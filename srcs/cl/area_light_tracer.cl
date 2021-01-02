t_color	direct_light_plastic_sample_material(t_material material,
											t_shade_rec *shade_rec,
											t_color *f, float *pdf, float *weight,
											t_texture_manager texture_manager,
											float4 *state)
{
	// sample microfacet at given point
	float alphaSquared = material.exp * material.exp;
	float4 m = sample_ggx_distriburion(shade_rec->normal, alphaSquared, state);

	// calculate Fresnel equation for given microfacet
	float eta = material.kr;
	float F = fresnel_dielectric(shade_rec->ray.direction, m, eta);

	float4 wi;
	if (GPURnd(state) < F)
	{
		wi = get_reflected_vector(shade_rec->ray.direction, m);
	}
	else
	{
		*pdf = 0.0f;
		return (*f);
		float4 u, v, w;

		build_from_w(&u, &v, &w, shade_rec->normal);
		wi = local_dir(&u, &v, &w, random_cosine_direction(state));
	}

	plastic_evaluate(material, shade_rec, f, pdf, weight,
					texture_manager, state, wi);
}

/* sample f*/
t_color	direct_light_sample_material(t_material material, t_shade_rec *shade_rec,
						t_color *f, float *pdf, float *weight,
						t_texture_manager texture_manager,
						uint2 *seed, float4 *state)
{
	if (material.type == matte || material.type == phong)
	{
		*pdf = 0.0f;
		*f = (t_color){0.0f, 0.0f, 0.0f, 0.0f};
		// return (matte_sample_material(material, shade_rec, f, pdf, weight,
									// texture_manager, state));
	}
	else if (material.type == mirror)
	{
		return (mirror_sample_material(material, shade_rec, f, pdf, weight,
									   texture_manager, state));
	}
	else if (material.type == conductor)
	{
		return (conductor_sample_material(material, shade_rec, f, pdf, weight,
										  texture_manager, state));
	}
	else if (material.type == plastic)
	{
		return (direct_light_plastic_sample_material(material, shade_rec, f, pdf,
													 weight, texture_manager,
													 state));
	}
	else if (material.type == dielectric)
	{
		return (dielectric_sample_material(material, shade_rec, f, pdf, weight,
									texture_manager, state));
	}
	else if(material.type == emissive)
	{
		*pdf = 0.0f;
	}
	return ((t_color){ 0.0f, 0.0f, 0.0f, 0.0f });
}

t_color	area_light_tracer(t_ray ray, t_scene scene, t_rt_options options,
						t_sampler_manager sampler_manager, uint2 *seed,
						float4 *state)
{
	t_shade_rec	shade_rec;

	t_color	color;
	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	t_color	beta;
	beta = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };

	bool	continue_loop = true;

	uchar	depth = 0;

	shade_rec.ray = ray;
	while (depth < options.depth)
	{
		if (scene_intersection(scene, ray, &shade_rec))
		{
			t_instance instance = get_instance(scene.instance_manager,
											shade_rec.id);
			t_material material = get_instance_material(
									scene.instance_manager,
									instance);

			//direct lightning
			color = color_sum(color,
							color_multi(beta,
									area_light_shade(scene,
													sampler_manager,
													material,
													shade_rec,
													options,
													seed)));

			t_color	f;
			float	pdf;
			float	weight;
			float	bsdf;

			/* scatter */
			direct_light_sample_material(material, &shade_rec, &f, &pdf,
										&weight,
										scene.instance_manager.tex_mngr,
										seed, state);

			if (is_black(f) || pdf <= 0.001f)
				break;

			/* beta = beta * f * dot(n, wi) * invPI / pdf */
			// beta = color_multi(beta,
			beta = color_multi(float_color_multi(1.0f / pdf, f), beta);
		}
		else
		{
			color = color_sum(color, color_multi(beta, _get_enviroment_light()));
			break;
		}
		depth++;
	}
	return (color);
}
