#include "world.h"

bool	intersection(t_ray ray, t_obj obj, float *tr)
{
	if (obj.type == sphere)
	{
		return (sphere_intersection(ray, obj, &tr));
	}
	else if (obj.type == plane)
	{
		return (plane_intersection(ray, obj, &tr));
	}
	else if (obj.type == cylinder)
	{
		return cylinder_intersection(ray, obj, &tr);
	}
	else if (obj.type == cone)
	{
		return (cone_intersection(ray, obj, &tr));
	}
	else if (obj.type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, &tr));
	}
	else if (obj.type == torus)
	{
		return torus_intersecion(ray, obj, &tr);
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
						const int seed0, const int seed1)
{
	t_ray	ray = camray;
	float3	accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3	mask = (float3)(1.0f, 1.0f, 1.0f);
	float	t;   
	int		hitobj_id = 0; 

	for (int bounces = 0; bounces < BOUNCES; bounces++)
	{
		if (!intersect_scene(objects, ray, &t, &hitobj_id, nobjects))
			return accum_color += mask * (float3)(100.15f, 100.15f, 100.25f);
		else
		{
			accum_color.x = (objects[hitobj_id].material.color >> 16) & 0xff;
			accum_color.y = (objects[hitobj_id].material.color >> 8) & 0xff;
			accum_color.z = objects[hitobj_id].material.color & 0xff;
			return accum_color;
		}
	}

	return (float3)(255.0f, 255.0f, 255.0f);
}
