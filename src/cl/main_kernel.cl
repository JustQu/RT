/**
**@brief
** получить цвет пикселя в позиции x,y экрана, используя камеру camera
** и объекты сцены
*/
int		get_pixel_color(int x, int y,
						t_scene scene,
						t_render_options options,
						t_sampler_manager sampler_manager,
						uint2 *seed)
{
	t_ray			ray;
	t_color			color;
	float3			test = (float3)(0.0f, 0.0f, 0.0f);
	t_sampler		ao_sampler;
	t_sampler		camera_sampler;

	color.value = 0;
	ao_sampler = get_sampler(sampler_manager, options.sampler_id);
	// ao_sampler.type = none;
	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, scene.camera.sampler_id);
		camera_sampler.count = get_global_id(0) * camera_sampler.num_samples;
	}
	if (0) //path tracing
	{
		ray = cast_camera_ray(scene.camera, x, y, sampler_manager, 0, seed);
		for (int i = 0; i < SAMPLES; i++)
			test += path_tracing(ray, scene, options, &x, &y);
		color.r = test.x / SAMPLES * 255;
		color.g = test.y / SAMPLES * 255;
		color.b = test.z / SAMPLES * 255;
	}
	else if (ao_sampler.type == none) //без антиалиасинга
	{
		ray = cast_camera_ray(scene.camera, x, y, sampler_manager, &camera_sampler, seed);
		// color = ray_trace(ray, scene, options);
	}
	else //антиалиасинг сгенерированный заранее на цпу
	{
		ao_sampler.count = get_global_id(0) * ao_sampler.num_samples;
		float2	sp = sample_unit_square(&ao_sampler, sampler_manager.samples, seed);
		float	dx = x + sp.x;
		float	dy = y + sp.y;

		for (int j = 0; j < ao_sampler.num_samples; j++)
		{
			sp = sample_unit_square(&ao_sampler, sampler_manager.samples, seed);
			dx = x + sp.x;
			dy = y + sp.y;

			ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager, &camera_sampler, seed);
			// color = ray_trace(ray, scene, options);

			/* accumulate color */
			test.x += color.r;
			test.y += color.g;
			test.z += color.b;
		}

		/* normalize accumulated color */
		color.r = test.x / ao_sampler.num_samples;
		color.g = test.y / ao_sampler.num_samples;
		color.b = test.z / ao_sampler.num_samples;
	}
	return (color.value);
}

void	init_scene(t_scene *scene, __constant t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__constant t_light *lights, int nlights,
					t_camera camera, t_light ambient_light,
					t_ambient_occluder ambient_occluder)
{
	scene->objects = objects;
	scene->nobjects = nobjects;
	scene->triangles = triangles;
	scene->ntriangles = ntriangles;
	scene->lights = lights;
	scene->nlights = nlights;
	scene->camera = camera;
	scene->ambient_light = ambient_light;
	scene->ambient_occluder = ambient_occluder;
}

void	init_sampler_manager(t_sampler_manager *sampler_manager,
							__global t_sampler *samplers,
							__global float2 *samples,
							__global float2 *disk_samples,
							__global float3 *hemisphere_samples)
{
	sampler_manager->samplers = samplers;
	sampler_manager->samples = samples;
	sampler_manager->disk_samples = disk_samples;
	sampler_manager->hemisphere_samples = hemisphere_samples;
}

/*
** Поскольку драйвер убивает кернел если он выполняется дольше чем 0,5 секунды,
** нам надо  его уменьшить. При каждом вызове будет считать по одной точке антиалиасинга.
** В дальнейшем когда будут сделаны материалы / преломления / отражения можно будет еще  ** больше разбить кернел чтобы избежать дивергенции кода.
*/
__kernel void	main(__global float3 *image,
				int step,

				__constant t_obj *objects, int nobjects,
				__constant t_triangle *triangles, int ntriangles,
				__constant t_light *lights, int nlights,
				t_camera camera,
				t_light ambient_light,
				t_ambient_occluder ambient_occluder,

				t_render_options options,

				__global t_sampler *samplers,
				__global float2 *samples,
				__global float2 *disk_samples,
				__global float3 *hemisphere_samples)
{
	int					global_id;
	int					x;
	int					y;
	uint2				seed;
	t_scene				scene;
	t_sampler_manager	sampler_manager;

	t_ray				ray;
	t_color				color;
	t_sampler			camera_sampler;
	t_sampler			ao_sampler;

	/* init some variables */
	global_id = get_global_id(0);
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.width;
	seed.x = global_id;
	seed.y = get_local_id(0) + get_group_id(0);
	seed.y = random(&seed);
	init_scene(&scene, objects, nobjects, triangles, ntriangles, lights, nlights, camera, ambient_light, ambient_occluder);
	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	ao_sampler = get_sampler(sampler_manager, options.sampler_id);
	ao_sampler.count = global_id * ao_sampler.num_samples + step;

	if (step != 0)
	{
		ao_sampler.jump = (random(&seed) % ao_sampler.num_sets) * ao_sampler.num_samples;
		options.ambient_occluder_sampler.jump = (random(&seed) % options.ambient_occluder_sampler.num_sets) * options.ambient_occluder_sampler.num_samples;
	}
	else
		image[global_id] = (float3)(0, 0, 0);

	float2	sp = sample_unit_square(&ao_sampler, sampler_manager.samples, &seed);
	float	dx = x + sp.x;
	float	dy = y + sp.y;

	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, scene.camera.sampler_id);
		camera_sampler.count = global_id * camera_sampler.num_samples + step;
		if (step != 0)
			camera_sampler.jump = (random(&seed) % camera_sampler.num_sets) * camera_sampler.num_samples;
	}

	ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager, &camera_sampler, &seed);
	color = ray_trace(ray, scene, options, sampler_manager, &seed);

	float3 rgb;
	rgb.x = color.r;
	rgb.y = color.g;
	rgb.z = color.b;
	image[global_id] += rgb;
}

__kernel void del(
				__global uint *output_image,

				__constant t_obj *objects, int nobjects,
				__constant t_triangle *triangles, int ntriangles,
				__constant t_light *lights, int nlights,
				t_camera camera,
				t_light ambient_light,

				t_render_options options,

				__global t_sampler *samplers,
				__global float2 *samples,
				__global float2 *disk_samples,
				__global float3 *hemisphere_samples)
{
	uint2				seed;
	int					global_id;
	int					x;
	int					y;
	t_scene				scene;
	t_sampler_manager	sampler_manager;

	global_id = get_global_id(0);
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.height;
	seed.x = global_id;
	seed.y = get_local_id(0);
	t_ambient_occluder ambient_occluder;
	// seed.y = random(&seed);

	init_scene(&scene, objects, nobjects, triangles, ntriangles, lights, nlights, camera, ambient_light, ambient_occluder);
	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	// put_pixel(image, x, y, color);
	output_image[global_id] = get_pixel_color(x, y, scene, options, sampler_manager, &seed);
}
