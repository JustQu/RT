float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

float4	get_plane_normal(t_obj plane)
{
	return (float4)(0.0f, 1.0f, 0.0f, 0.0f);
}

float4	get_cylinder_normal(float4 point, t_obj cylinder, float m)
{
	return (normalize(point - (float4)(0.0f, m, 0.0f, 0.0f)));
}

float4	get_cone_normal(float4 point, t_obj cone, float m)
{
	// float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cone.r2 * (float4)(0.0f, 1.0f, 0.0f, 0.0f) * m));
}

float4	get_paraboloid_normal(float4 point, t_obj paraboloid, float m)
{
	return (normalize(point - (float4)(0.0f, m + paraboloid.r, 0.0f, 0.0f)));
	// float m = hit_info.dv * hit_info.t + hit_info.xv;
	// return (normalize(point - paraboloid.origin - paraboloid.direction * (m +
	// 	paraboloid.r)));
}

 float4	get_triangle_normal(t_triangle triangle)
{
	return (triangle.normal);
}

float4	get_torus_normal(float4 point, t_obj torus)
{
	float p = torus.r * torus.r + torus.r2 * torus.r2;
	float s = point.x * point.x + point.y * point.y + point.z * point.z;

	return normalize((float4)(
		4.0f * point.x * (s - p),
		4.0f * point.y * (s - p + 2.0f * torus.r * torus.r),
		4.0f * point.z * (s - p),
		0.0f));
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

float4	get_object_normal(float4 point, t_obj object, t_hit_info hit_info, t_type type)
{
	if (type == sphere)
	{
		return get_sphere_normal(point, object);
	}
	else if (type == plane)
	{
		return (get_plane_normal(object));
	}
	// else if (type == cylinder)
	// {
		// return (get_cylinder_normal(point, object));
	// }
	else if (type == cone)
	{
		// return (get_cone_normal(point, object, hit_info));
	}
	else if (type == paraboloid)
	{
		// return (get_paraboloid_normal(point, object, hit_info));
	}
	else if (type == torus)
	{
		return (get_torus_normal(point, object));
	}
	else if (type == box)
	{
		return (get_box_normal(point, object, hit_info));
	}
	else if (type == disk)
	{
		return (get_plane_normal(object));
	}
	else if (type == rectangle)
		return (float4)(0.0f, 0.0f, 0.0f, 0.0f);
}

float4	transform_normal(float4 normal, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * normal.x + matrix.s4 * normal.y + matrix.s8 * normal.z,
		matrix.s1 * normal.x + matrix.s5 * normal.y + matrix.s9 * normal.z,
		matrix.s2 * normal.x + matrix.s6 * normal.y + matrix.sA * normal.z,
		0.0f);
}

float4	get_instance_normal(t_instance_manager instance_mngr,
							t_instance instance,
							t_shade_rec *shade_rec)
{
	float4		normal;

	if (instance.type == triangle)
		normal = get_triangle_normal(instance_mngr.triangles[instance.object_id]);
	else
		normal = get_object_normal(shade_rec->local_hit_point,
									instance_mngr.objects[instance.object_id],
									shade_rec->hit_info,
									instance.type);
	return (normal);
}
