#include "world.h"

cl_float4 get_obj_normal(cl_float4 hitpoint, t_obj obj)
{
	int		type = obj.type;

	if (type == sphere)
		return normalize(hitpoint - obj.origin);
	else if (type == plane)
		return normalize(obj.direction);
}

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
