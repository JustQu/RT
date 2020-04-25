// #include "world.h"

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
