float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = -l + 2 * dot(l, n) * n;
	return normalize(r);
}

//TODO(dmelessa): shading both sides of surface ยง14
bool	scene_intersection(t_ray ray, t_shade_rec *shade_rec, t_scene scene)
{
	float		t;
	t_hit_info	last_rec;

	last_rec.t = K_HUGE_VALUE;
	shade_rec->hit_an_object = false;
	shade_rec->hit_a_triangle = false;

	for (int i = 0; i < scene.nobjects; i++)
	{
		if (is_intersect(ray, scene.objects[i], &shade_rec->hit_info)
			&& shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_an_object = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}

	for (int i = 0; i < scene.ntriangles; i++)
	{
		if (triangle_intersection(ray, scene.triangles[i], &shade_rec->hit_info)
			&& shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_a_triangle = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}

	shade_rec->hit_info = last_rec;
	return (shade_rec->hit_an_object || shade_rec->hit_a_triangle);
}

//todo: move normal computation to ray_trace_function
t_color	ray_trace(t_ray ray, t_scene scene, t_render_options options, t_sampler_manager sampler_manager, uint2 *seed)
{
	t_shade_rec	shade_rec;
	t_color		color;

	color.value = options.background_color.value;
	if (scene_intersection(ray, &shade_rec, scene))
	{
		/* save ray for specular reflection */
		shade_rec.ray = ray;

		/* compute hit point */
		shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

		/* shade ovject if it was triangle */
		if (shade_rec.hit_a_triangle)
		{
			/* compute triangle normal */
			shade_rec.normal = get_triangle_normal(scene.triangles[shade_rec.id]);

			/* shade triangle */
			color = shade_object(scene.triangles[shade_rec.id].material, shade_rec, scene, sampler_manager,options, seed);
		}

		/* shade object if it was not triangle */
		else
		{
			/* get object normal */
			shade_rec.normal = get_object_normal(shade_rec.hit_point,
				scene.objects[shade_rec.id], shade_rec.hit_info);
			shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
				shade_rec.normal : -shade_rec.normal;

			/* shade object */
			color = shade_object(scene.objects[shade_rec.id].material, shade_rec, scene, sampler_manager, options, seed);
		}
	}
	return (color);
}
