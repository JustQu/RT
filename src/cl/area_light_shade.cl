t_color		area_light_shade_phong(t_material material,
									t_shade_rec shade_rec,
									t_scene scene,
									t_sampler_manager sampler_manager,
									t_render_options options,
									uint2 *seed)
{
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	/* revert camera ray for specular light */
	shade_rec.ray.direction = -shade_rec.ray.direction;

	if (options.ambient_occlusion) /* ambient occlusion */
	{
		color = ambient_occlusion_l(scene, sampler_manager, &options.ambient_occluder_sampler, shade_rec, seed);
		color = color_multi(color, material.color);
	}
	else /* compute constant ambient light using ka coefficent of the materail */
	{
		color = lambertian_rho(material.ka, material.color);
		color_tmp = get_light_radiance(scene.ambient_light);
		color = color_multi(color, color_tmp);
	}

	/* compute sahding for each light source */
	for (int i = 0; i < scene.nlights; i++)
	{
		bool	in_shadow = false;

		/* compute light direction at hit point */
		light_direction = get_light_direction(scene.lights[i], shade_rec);

		/* multiplying by 0.999f to avoid self shadowing error */
		t_ray	shadow_ray = {.origin = shade_rec.hit_point * 0.999f, .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(scene.lights[i], shadow_ray, shade_rec, scene);

		if (!in_shadow)
		{
			/* compute angle between normal at the hit point and light direction */
			dirdotn = dot(shade_rec.normal, light_direction);

			/* if angle > 0 then hit point is receivingl light */
			if (dirdotn > 0.0f)
			{
				/* compute glossy_specular coefficient */
				float a = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, material.ks, material.exp) ;

				/* compute diffuse color */
				color_tmp = lambertian_f(material.kd, material.color);

				/* sum lambertian color and glossy specular color */
				color_tmp = color_sum(color_tmp, float_color_multi(a, scene.lights[i].color));

				/* compute how much light the point receives depends on angle between the normal at this point and light direction */
				color_tmp.r = clamp(scene.lights[i].ls * scene.lights[i].color.r * color_tmp.r / 255.0f * dirdotn, 0.0f, 255.0f);
				color_tmp.b = clamp(scene.lights[i].ls * scene.lights[i].color.b * color_tmp.b / 255.0f * dirdotn, 0.0f, 255.0f);
				color_tmp.g = clamp(scene.lights[i].ls * scene.lights[i].color.g * color_tmp.g / 255.0f * dirdotn, 0.0f, 255.0f);
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

t_color		area_light_shade(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_render_options render_options,
							uint2 *seed)
{
	t_color	color;

	// if (material.type == phong)
	// 	area_light_shade_phong(material, shade_rec, scene, sampelr_manager, render_options, seed);
	// else if (material.type == emissive)

	// else

	return (color);
}
