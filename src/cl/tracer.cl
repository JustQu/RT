#include "world.h"
# define SAMPLES 500
# define BOUNCES 8
# define TRACING 0

float3		path_traycing(t_ray camray,
						__constant t_obj *objects, int nobjects,
						unsigned int *seed0, unsigned int *seed1)
{
	t_ray	ray = camray;
	float3	accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3	mask = (float3)(1.0f, 1.0f, 1.0f);

	for (int bounces = 0; bounces < BOUNCES; bounces++)
	{
		float	t;
		int		hitobj_id = 0;
		if (!intersect_scene(objects, ray, &t, &hitobj_id, nobjects))
			return accum_color += mask * (float3)(0.05f, 0.05f, 0.05f);
		
		t_obj	hit_obj = objects[hitobj_id];
		//return hit_obj.material.color;
		/* compute the hitpoint using the ray equation */
		float4	hitpoint = ray.origin + ray.direction * t;
		
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		float4 normal = get_obj_normal(hitpoint, hit_obj);
		float4 normal_facing = dot(normal, ray.direction) < 0.0f ? normal : normal * (-1.0f);

		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
		float rand1 = 2.0f * PI * get_random(seed0, seed1);
		float rand2 = get_random(seed0, seed1);
		float rand2s = sqrt(rand2);

		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float4 w = normal_facing;
		float4 axis = fabs(w.x) > 0.1f ? (float4)(0.0f, 1.0f, 0.0f, 0.0f) : (float4)(1.0f, 0.0f, 0.0f, 0.0f);
		float4 u = normalize(cross(axis, w));
		float4 v = cross(w, u);

		/* use the coordinte frame and random numbers to compute the next ray direction */
		float4 newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));

		/* add a very small offset to the hitpoint to prevent self intersection */
		ray.origin = hitpoint + normal_facing * EPSILON;
		ray.direction = newdir;

		/* add the colour and light contributions to the accumulated colour */
		accum_color += mask * hit_obj.material.emission; 

		/* the mask colour picks up surface colours at each bounce */
		mask *= hit_obj.material.color; 
		
		/* perform cosine-weighted importance sampling for diffuse surfaces*/
		mask *= dot(newdir, normal_facing); 
	}

	return accum_color;
}

float3		ray_tracing(t_ray camray, const t_camera cam,
						__constant t_obj *objects, int nobjects)
{
	t_ray	ray = camray;
	float	t;
	int		hitobj_id = 0;
	if (!intersect_scene(objects, ray, &t, &hitobj_id, nobjects))
		return (float3)(0.05f, 0.05f, 0.05f);

	t_obj	hit_obj = objects[hitobj_id];
	return hit_obj.material.color;
}

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

__kernel void tracer(
				__global uint *output_image,
				__constant t_obj *objects, int nobjects,
				t_camera camera,
				__constant t_triangle *triangles)
{
	private int		global_id = get_global_id(0);
	unsigned int	x = global_id % DEFAULT_WIDTH;
	unsigned int	y = global_id / DEFAULT_WIDTH;

	float3 color = (float3)(0.0f, 0.0f, 0.0f);
	t_ray	camray = cast_primal_ray(camera, x, y);
	
	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
	{
		if (TRACING)
		{
			float invSamples = 1.0f / SAMPLES;
			for (int i = 0; i < SAMPLES; i++)
				color += path_traycing(camray, objects, nobjects, &x, &y) * invSamples;
		}
		else
		{
			color = ray_tracing(camray, camera, objects, nobjects);
		}

		int finalcolor = (((int)(color.x * 255)) << 16) | (((int)(color.y * 255)) << 8) | ((int)(color.z * 255));
		output_image[global_id] = finalcolor;
	}
}
