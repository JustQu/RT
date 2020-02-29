#include "world.h"
# define BOUNCES 10

bool	intersection(t_ray ray, t_obj obj, float *tr)
{
	if (obj.type == sphere)
	{
		return (sphere_intersection(ray, obj, tr));
	}
	else if (obj.type == plane)
	{
		return (plane_intersection(ray, obj, tr));
	}
	else if (obj.type == cylinder)
	{
		return cylinder_intersection(ray, obj, tr);
	}
	else if (obj.type == cone)
	{
		return (cone_intersection(ray, obj, tr));
	}
	else if (obj.type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, tr));
	}
	else if (obj.type == torus)
	{
		return torus_intersecion(ray, obj, tr);
	}
	return (false);
}

bool	intersect_scene(__constant t_obj *objects, t_ray ray, float *t, int *object_id, const int nobjects)
{
	/* initialise t to a very large number, 
	so t will be guaranteed to be smaller
	when a hit with the scene occurs */

	float inf = 1e20f;
	*t = inf;

	/* check if the ray intersects each object in the scene */
	for (int i = 0; i < nobjects; i++)
	{
		t_obj obj = objects[i]; /* create local copy of object */
		float hitdistance;

		/* keep track of the closest intersection and hitobject found so far */
		if (intersection(ray, obj, &hitdistance))
		{
			if (hitdistance != 0.0f && hitdistance < *t)
			{
				*t = hitdistance;
				*object_id = i;
			}
		}
	}
	return *t < inf; /* true when ray interesects the scene */
}

float3		get_point_color(t_ray camray,
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
			return accum_color += mask * (float3)(0.5f, 0.5f, 0.5f);
		
		t_obj	hit_obj = objects[hitobj_id];
		return hit_obj.material.color;
		/* compute the hitpoint using the ray equation */
		float4	hitpoint = ray.origin + ray.direction * t;
		
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		float4 normal = normalize(hitpoint - hit_obj.origin); 
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
