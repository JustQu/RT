float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

float4	get_plane_normal(t_obj plane, t_hit_info hit_info)
{
	if (hit_info.dv < 0.0F)
		return plane.direction;
	else
		return -(plane.direction);
}

float4	get_cylinder_normal(float4 point, t_obj cylinder, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cylinder.origin - cylinder.direction * m));
}

float4	get_cone_normal(float4 point, t_obj cone, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cone.origin - cone.r2 * cone.direction * m));
}

float4	get_paraboloid_normal(float4 point, t_obj paraboloid, t_hit_info hit_info)
{
	if (paraboloid.maxm > 0.0f)
		return (normalize(point - paraboloid.origin - paraboloid.direction *
			(hit_info.m + paraboloid.r)));
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - paraboloid.origin - paraboloid.direction * (m +
		paraboloid.r)));
}

 float4	get_triangle_normal(t_triangle triangle)
{
	return (triangle.normal);
}

float4	get_torus_normal(float4 point, t_obj torus, t_hit_info hit_info)
{
	float	k;
	float	m;
	float4	A;

	point = 1.0001f * point;
	k = dot(point - torus.origin, torus.direction);
	A = point - k * torus.direction;
	m = sqrt(torus.r2 * torus.r2 - k * k);
	return normalize(point - A - (torus.origin - A) * (m / (torus.r + m)));
}

float4	get_box_normal(float4 point, t_obj box, t_hit_info hit_info)
{
	if (hit_info.m == 0)
	{
		return ((float4)(-1.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 1)
	{
		return ((float4)(0.0f, -1.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 2)
	{
		return ((float4)(0.0f, 0.0f, -1.0f, 0.0f));
	}
	else if (hit_info.m == 3)
	{
		return ((float4)(1.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 4)
	{
		return ((float4)(0.0f, 1.0f, 0.0f, 0.0f));
	}
	else if (hit_info.m == 5)
	{
		return ((float4)(0.0f, 0.0f, 1.0f, 0.0f));
	}
}

float4	get_object_normal(float4 point, t_obj object, t_hit_info hit_info)
{
	if (object.type == sphere)
	{
		return get_sphere_normal(point, object);
	}
	else if (object.type == plane)
	{
		return (get_plane_normal(object, hit_info));
	}
	else if (object.type == cylinder)
	{
		return (get_cylinder_normal(point, object, hit_info));
	}
	else if (object.type == cone)
	{
		return (get_cone_normal(point, object, hit_info));
	}
	else if (object.type == paraboloid)
	{
		return (get_paraboloid_normal(point, object, hit_info));
	}
	else if (object.type == torus)
	{
		return (get_torus_normal(point, object, hit_info));
	}
	else if (object.type == box)
	{
		return (get_box_normal(point, object, hit_info));
	}
	else if (object.type == disk)
	{
		return (get_plane_normal(object, hit_info));
	}
}
