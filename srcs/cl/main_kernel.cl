void	init_scene(t_scene *scene,
					__constant t_instance *instances, int ninstances,
					__global t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__global t_matrix *matrices, int nmatrices,
					__constant t_light *lights, int nlights,
					__global t_bvh_node *bvh,

					__global t_texture *textures,
					__global float4 *ranvec,
					__global int *perm_x,
					__global int *perm_y,
					__global int *perm_z,

					t_camera camera, t_light ambient_light,
					t_ambient_occluder ambient_occluder)
{
	scene->instance_manager.instances = instances;
	scene->instance_manager.ninstances = ninstances;
	scene->instance_manager.objects = objects;
	scene->instance_manager.nobjects = nobjects;
	scene->instance_manager.triangles = triangles;
	scene->instance_manager.ntriangles = ntriangles;
	scene->instance_manager.matrices = matrices;
	scene->instance_manager.nmatrices = nmatrices;

	scene->instance_manager.tex_mngr.textures = textures;
	scene->instance_manager.tex_mngr.perlin_noise = ranvec;
	scene->instance_manager.tex_mngr.perm_x  = perm_x;
	scene->instance_manager.tex_mngr.perm_y = perm_y;
	scene->instance_manager.tex_mngr.perm_z = perm_z;

	scene->lights = lights;
	scene->nlights = nlights;
	scene->bvh = bvh;
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

float		hash(float seed)
{
	float res;
	return fract(sin(seed) * 43758.5453123, &res);
}

										//Pos of argument on host
__kernel  __attribute__((work_group_size_hint(32, 1, 1)))
void main_kernel(__global t_color *image,	//0
				int step,						//1

				__constant t_instance *instances, int ninstances, //2, 3
				__global t_obj *objects, int nobjects,		//4, 5
				__constant t_triangle *triangles, int ntriangles, //6, 7
				__global t_matrix *matrices, int nmatrices,	//8, 9
				__constant t_light *lights, int nlights,		//10, 11
				t_camera camera,		//12
				t_light ambient_light,	//13
				t_ambient_occluder ambient_occluder, //14

				__global t_bvh_node	*bvh, //15

				t_rt_options options, //16

				__global t_sampler *samplers, //17
				__global float2 *samples, //18
				__global float2 *disk_samples,	//19
				__global float3 *hemisphere_samples, //20
				uint num,	//21

				__global t_texture *textures, //22
				__global float4 *ranvec,	//23
				__global int *perm_x,		//24
				__global int *perm_y,		//25
				__global int *perm_z)		//26
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

	/* Инициализируем нужные переменные и структуры */
	global_id = get_global_id(0);
	// if (global_id == 0)
	// 	printf("Rendering: %f%%\n", step / options.spp * 100.0f);
	x = global_id % camera.viewplane.width;
	y = global_id / camera.viewplane.width;

	seed.x = global_id + x + num;
	seed.y = y + get_local_id(0) + get_group_id(0);
	seed.y = random(&seed);
	float4 state;
	float2 s;
	s.x = seed.x;
	s.y = seed.y / ((float)num + 1.0f) * 43534.0f - num;
	state.x = hash(s.x + seed.x);
	state.y = hash(s.y + state.x);
	state.z = hash(state.x + state.y);
	state.w = hash(num + s.y - state.x * state.y);
	GPURnd(&state);

	init_scene(&scene,
				instances, ninstances, objects, nobjects,
				triangles, ntriangles, matrices, nmatrices,
				lights, nlights, bvh,
				textures, ranvec, perm_x, perm_y, perm_z,
				camera, ambient_light, ambient_occluder);

	init_sampler_manager(&sampler_manager, samplers, samples, disk_samples, hemisphere_samples);

	options.sampler = get_sampler(sampler_manager, options.aa_id);
	options.sampler.jump = ((random(&seed)) % options.sampler.num_sets) *
							options.sampler.num_samples;
	options.sampler.count = global_id + num;

	sampler_manager.sampler = &options.sampler;

	// t_sampler ssp = get_sampler(sampler_manager, 4);
	// if (global_id == 0)
	// 	for (int i = 0; i < ssp.num_samples * ssp.num_sets; i++)
	// 	{
	// 		float2 s =  sample_unit_square(&ssp,sampler_manager.samples, &seed);
	// 		printf("%f %f++++", s.x, s.y);
	// 	}
	/* получаем семплер для антиалиасинга и текущий шаг. */
	// ao_sampler = get_sampler(sampler_manager, options.aa_id);
	// ao_sampler.count = global_id * ao_sampler.num_samples + step;

	// ao_sampler.jump = ((num + random(&seed)) % ao_sampler.num_sets) * ao_sampler.num_samples;
	// ao_sampler.count = global_id + num;

	// options.ambient_occluder_sampler.jump = (random(&seed) % options.ambient_occluder_sampler.num_sets) * options.ambient_occluder_sampler.num_samples;
	// options.ambient_occluder_sampler.count = global_id;

	if (options.reset == 1)
	{
		image[global_id] = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};
	}

	/* */
	float2	sp = sample_unit_square(&options.sampler, sampler_manager.samples, &seed);
	// float dx = x + sp.x;
	// float dy = y + sp.y;
	float	dx = x + GPURnd(&state);
	float	dy = y + GPURnd(&state);

	if (scene.camera.type == thin_lens)
	{
		camera_sampler = get_sampler(sampler_manager, 0);
		camera_sampler.count = global_id;
		// if (camera_sampler.count % camera_sampler.num_samples == 0)
		camera_sampler.jump = ((random(&seed)) % camera_sampler.num_sets) * camera_sampler.num_samples;
		// if (step != 0)
		// 	camera_sampler.jump = ((num + random(&seed)) % camera_sampler.num_sets) * camera_sampler.num_samples;
	}

	ray = cast_camera_ray(scene.camera, dx, dy, sampler_manager,
						&camera_sampler, &seed, &state);

	if (options.tracer_type == ray_caster)
	{
		color = ray_cast(ray, scene, options, sampler_manager, &seed);
	}
	else if (options.tracer_type == direct_lightning)
	{
		color = area_light_tracer(ray, scene, options, sampler_manager, &seed,
								&state);
	}
	else if (options.tracer_type == path_tracer)
	{
		color = trace(ray, scene, options, sampler_manager, &seed, &state);
	}


	// color = global_shade(ray, scene, options, sampler_manager, &seed, &state);

	// color = area_light_tracer(ray, scene, options, sampler_manager, &seed);


	// color = path_tracer2(ray, scene, options, sampler_manager, &seed, &state,
						// &options.ambient_occluder_sampler);

	// color = path_trace_pdf(ray, scene, options, sampler_manager, &seed, &state);

	image[global_id] = color_sum(image[global_id], color);
}
