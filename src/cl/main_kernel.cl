// #include "world.h"
// #include "cl_rt.h"


// #include "ray_tracer.cl"
// #include "path_tracer.cl"
// #include "camera.cl"
// #include "color.cl"
// #include "random.cl"
// #include "utils.cl"
// #include "light.cl"
// #include "normal.cl"
// #include "intersection.cl"
// #include "solver.cl"
// #include "sampler.cl"

// #define EPSILON 1e-5f

/**
**@brief
** получить цвет пикселя в позиции x,y экрана, используя камеру camera
** и объекты сцены
*/
 int		get_pixel_color(t_camera camera,
					__constant t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__constant t_light *lights, int nlights,
					t_light ambient_light,
					int x, int y,
					t_render_options options,
					t_sampler_info sampler_info,
					__global float2 *sampler_set)
{
#if 1
	t_ray		ray;
	t_color		color;
	float3		test = (float3)(0.0f, 0.0f, 0.0f);

	color.value = 0;
	if (0) //path tracing
	{
		ray = cast_camera_ray(camera, x, y);
		for (int i = 0; i < SAMPLES; i++)
		{
			test += path_tracing(ray,
						objects, nobjects,
						triangles, ntriangles,
						lights, lights,
						options,
						&x, &y);
		}
		color.r = test.x / SAMPLES * 255;
		color.g = test.y / SAMPLES * 255;
		color.b = test.z / SAMPLES * 255;
	}
	else if (sampler_info.type == jitter)//антиалиасинг, сделанный Бориславом
	{
		float jitterMatrix[4 * 2] = {
			-1.0/4.0,  3.0/4.0,
	 		3.0/4.0,  1.0/3.0,
			-3.0/4.0, -1.0/4.0,
	 		1.0/4.0, -3.0/4.0,
		};
		for (int sample = 0; sample < 4; ++sample)
		{
			float dx = (x + jitterMatrix[2 * sample]);
			float dy = (y + jitterMatrix[2 * sample + 1]);
			ray = cast_camera_ray(camera, dx, dy);
			color = ray_trace(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
			test.x += color.r;
			test.y += color.g;
			test.z += color.b;
		}
		color.r = test.x / sampler_info.num_samples;
		color.g = test.y / sampler_info.num_samples;
		color.b = test.z / sampler_info.num_samples;
	}
	else if (sampler_info.type == none) //без антиалиасинга
	{
		ray = cast_camera_ray(camera, x, y);
		color = ray_trace(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
	}
	else //антиалиасинг сгенерированный заранее на цпу
	{
		int	count = get_global_id(0) / sampler_info.num_sets; //???
		for (int j = 0; j < sampler_info.num_samples; j++)
		{
			//get sample
			float2	sp = sample_unit_square(sampler_set, sampler_info, &count);
			float dx = x + sp.x;
			float dy = y + sp.y;
			ray = cast_camera_ray(camera, dx, dy);
			color = ray_trace(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
			test.x += color.r;
			test.y += color.g;
			test.z += color.b;
		}
		color.r = test.x / sampler_info.num_samples;
		color.g = test.y / sampler_info.num_samples;
		color.b = test.z / sampler_info.num_samples;
	}
	return (color.value);

#else //delete this
	t_ray		ray;
	t_hit_info	hit_info;
	t_shade_rec	shade_rec;
	float		mint = 10001.0f; //attention!
	int			i;
	for (i = 0; i < nobjects; i++)
	{
		if (is_intersect(ray, objects[i], &hit_info) &&
			hit_info.t < mint && hit_info.t > 1.0f)
		{
			mint = hit_info.t;
			hit_info.id = i;
		}
	}
	if (mint >= 1.0f && mint < 10000.0f)//atention!
	{
		//cast secondary rays
		return objects[hit_info.id].material.color;
	}
	else
		return 0x000000af;
#endif
}

/**
**NOTE: сейчас код использует везде один набор сэмлов
**		надо будет сделать разные сэмплы в разных местах
*/
__kernel void main(
				__global uint *output_image,
				__constant t_obj *objects, int nobjects,
				__constant t_triangle *triangles, int ntriangles,
				__constant t_light *lights, int nlights,
				t_camera camera,
				t_light ambient_light,
				t_render_options options,
				t_sampler_info sampler_info,
				__global float2 *samples)
{
	private int	global_id = get_global_id(0);;;;
	private int	x = global_id % DEFAULT_WIDTH;
	private int	y = global_id / DEFAULT_WIDTH;

	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
	{
		output_image[global_id] =
			get_pixel_color(camera, objects, nobjects, triangles, ntriangles,
							lights, nlights, ambient_light, x, y, options,
							sampler_info, samples);
	}
}
