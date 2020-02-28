#include "world.h"
# define SAMPLES 100

t_ray	cast_primal_ray(t_camera camera, int x, int y)
{
	t_ray	ray;
	float	px;
	float	py;

	px = (2 * ((x + 0.5f) / DEFAULT_WIDTH) - 1) * camera.angle * camera.ratio;
	py = (1 - 2 * (y + 0.5f) / DEFAULT_HEIGHT) * camera.angle;
	ray.origin = camera.origin;
	ray.direction = (float4)(px, py, 1.0f, 0.0f);//need to rotate vector if we have rotated camera
	ray.direction = normalize(ray.direction);
	return ray;
}

__kernel void raytracer(
				__global uint *output_image,
				__constant t_obj *objects, int nobjects,
				t_camera camera,
				__constant t_triangle *triangles)
{
	private int		global_id = get_global_id(0);
	unsigned int	x = global_id % DEFAULT_WIDTH;
	unsigned int	y = global_id / DEFAULT_WIDTH;

	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
	{
		float3 color = (float3)(0.0f, 0.0f, 0.0f);
		float invSamples = 1.0f / SAMPLES;
		t_ray	camray = cast_primal_ray(camera, x, y);

		for (int i = 0; i < SAMPLES; i++)
			color += get_point_color(camray, objects, nobjects, &x, &y) * invSamples;

		int finalcolor = (((int)(color.x * 255)) << 16) | (((int)(color.y * 255)) << 8) | ((int)(color.z * 255));
		output_image[global_id] = finalcolor;
	}
}
