#define _get_instance() get_instance(scene.instance_manager, shade_rec.id)
#define _get_instance_material() get_instance_material(scene.instance_manager,\
														instance)
#define _get_enviroment_light() options.background_color
#define is_black(color) (color.r <= 0.01f && color.g <= 0.01f && color.b <= 0.01f)

t_color	matte_sample_light(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_rt_options options,
							uint2 *seed, float4 *state)
{
	t_light	light;

	if (dot(shade_rec.normal, shade_rec.ray.direction) > 0.0f)
		shade_rec.normal = -shade_rec.normal;

	/* get random light
	** Note: not the best approach. Lights with bigger intensivity weights more
	*/
	light = scene.lights[(int)(GPURnd(state) * scene.nlights)];

	bool	in_shadow = false;

	float4	wi = get_light_direction2(scene, &light, shade_rec,
										sampler_manager, seed);
	wi = normalize(wi);
	if (options.shadows)
	{
		t_ray	shadow_ray = { .origin = shade_rec.hit_point
										+ 1e-2f * shade_rec.normal,
								.direction = wi };
		in_shadow = shadow_hit(scene, light, shadow_ray, shade_rec);
	}

	if (!in_shadow)
	{
		float	ndotwi = dot(shade_rec.normal, wi);

		if (ndotwi > 0.0f)
		{
			t_color	c = lambertian_f(material.kd,
									get_color(scene.instance_manager.tex_mngr,
									material, &shade_rec));

			float k = ndotwi
						* light_g(light, wi, shade_rec)
						/ light_pdf(light);
			return (float_color_multi(k,
								color_multi(light_l(light, wi),
											c)));
			return (color_multi(c,
							float_color_multi(ndotwi
												* light_g(light, wi, shade_rec)
												/ light_pdf(light),
											light_l(light, wi))));
		}
	}
	return ((t_color) { .r = 0.0f, .g = 0.0f, .b = 0.0f });
}

t_color	phong_sample_light(t_material material,
							t_shade_rec shade_rec,
							t_scene scene,
							t_sampler_manager sampler_manager,
							t_rt_options options,
							uint2 *seed)
{
	t_light	light;

	if (dot(shade_rec.normal, shade_rec.ray.direction) > 0.0f)
		shade_rec.normal = -shade_rec.normal;

	/* get random light
	** Note: not the best approach. Lights with bigger intensivity weights more
	*/
	light = scene.lights[random(seed) % scene.nlights];

	bool	in_shadow = false;

	float4	wi = get_light_direction2(scene, &light, shade_rec,
										sampler_manager, seed);
	if (options.shadows)
	{
		t_ray	shadow_ray = { .origin = shade_rec.hit_point
										+ 1e-4f * shade_rec.normal,
								.direction = wi };
		in_shadow = shadow_hit(scene, light, shadow_ray, shade_rec);
	}

	if (!in_shadow)
	{
		float	ndotwi = dot(shade_rec.normal, wi);

		if (ndotwi > 0.0f)
		{
			t_color	c = lambertian_f(material.kd,
									get_color(scene.instance_manager.tex_mngr,
									material, &shade_rec));

			if (light.type == point || light.type == directional)
			{
				c = color_sum(c, glossy_specular_f(shade_rec.ray.direction,
													shade_rec.normal, wi, ndotwi,
													material.ks, material.exp));
			}

			return (color_multi(c,
							float_color_multi(ndotwi
												* light_g(light, wi, shade_rec)
												/ light_pdf(light),
											light_l(light, wi))));
		}
	}
	return ((t_color) { .r = 0.0f, .g = 0.0f, .b = 0.0f });
}

/* shade surface */
t_color	sample_light(t_material material, t_shade_rec shade_rec, t_scene scene,
					t_sampler_manager sampler_manager, t_rt_options options,
					uint2 *seed, float4 *state)
{
	if (material.type == matte || material.type == plastic)
	{
		return (matte_sample_light(material, shade_rec, scene, sampler_manager,
									options, seed, state));
	}
	else if (material.type == phong)
	{
		return (phong_sample_light(material, shade_rec, scene, sampler_manager,
									options, seed));
	}
	else if (material.type == mirror)
	{
		/* don't shade if it is a mirror material */
		return ((t_color) { 0.0f, 0.0f, 0.0f, 0.0f });
	}
	else if (material.type == conductor)
	{
		return ((t_color) { 0.0f, 0.0f, 0.0f, 0.0f });
	}
	else if (material.type == dielectric)
	{
		return ((t_color) { 0.0f, 0.0f, 0.0f, 0.0f });
	}
	else if (material.type == emissive)
	{
		return ((t_color){ 1.0f, 1.0f, 1.0f, 0.0f });
	}
	return ((t_color){0.0f, 0.0f, 0.0f, 0.0f});
}

/* scatter */
t_color	matte_sample_material(t_material material, t_shade_rec *shade_rec,
							t_color *f, float *pdf, float *weight,
							t_texture_manager texture_manager,
							float4 *state)
{

	if (dot(shade_rec->normal, shade_rec->ray.direction) > 0.0f)
		shade_rec->normal = -shade_rec->normal;
	float4 u, v, w;

	build_from_w(&u, &v, &w, shade_rec->normal);
	float4 direction = local_dir(&u, &v, &w, random_cosine_direction(state));

	shade_rec->ray.origin = shade_rec->hit_point + shade_rec->normal * 1e-2f;
	shade_rec->ray.direction = direction;

	float ndotwi = dot(w, direction);
	*pdf = ndotwi * M_1_PI_F;

	/* todo: multiply by diffuse coefficient */
	*f = float_color_multi(*pdf,
						get_color(texture_manager, material, shade_rec));
	*weight = 1.0f;
	return (*f);
}

t_color	mirror_sample_material(t_material material, t_shade_rec *shade_rec,
							t_color *f, float *pdf, float *weight,
							t_texture_manager texture_manager, float4 *state)
{
	if (dot(shade_rec->normal, shade_rec->ray.direction) > 0.0f)
		shade_rec->normal = -shade_rec->normal;

	shade_rec->ray.origin = shade_rec->hit_point + 1e-4f * shade_rec->normal;

	shade_rec->ray.direction = get_reflected_vector(shade_rec->ray.direction,
													shade_rec->normal);

	// *f = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };
	*pdf = 1.0f;
	*weight = 1.0f;
	*f = get_color(texture_manager, material, shade_rec);
}

float	fresnel_conductor(float cos_theta)
{
	return (1.0f);
}

float	ggx_visibility(float roughness_sq, float cos_theta)
{
	float cos_theta_squared = cos_theta * cos_theta;
	float tan_theta_squared = (1.0f - cos_theta_squared) / cos_theta_squared;
	return (2.0f / (1.0f + sqrt(1.0f + roughness_sq * tan_theta_squared)));
}
float	ggx_visibility_term(float roughness_sq, float t0, float t1)
{
	return (ggx_visibility(roughness_sq, t0) * ggx_visibility(roughness_sq, t1));
}

float	ggx_visibility2(float a_sq, float4 w, float4 n, float4 m)
{
	float NdotW = dot(n, w);
	float MdotW = dot(m, w);
	if (MdotW * NdotW <= 0.0f)
		return 0.0f;

	float cosThetaSquared = NdotW * NdotW;
	float tanThetaSquared = (1.0f - cosThetaSquared) / cosThetaSquared;
	if (tanThetaSquared == 0.0f)
		return 1.0f;

	return 2.0f / (1.0f + sqrt(1.0f + a_sq * tanThetaSquared));
}

float	ggx_visibility_term2(float a_sq, float4 wo, float4 wi,
							float4 n, float4 m)
{
	return (ggx_visibility2(a_sq, wo, n, m) * ggx_visibility2(a_sq, wi, n, m));
}

float	ggx_normal_distribution(float roughness_sq, float cos_theta)
{
	float denom = (roughness_sq - 1.0f) * cos_theta * cos_theta + 1.0f;
	return (roughness_sq / (M_PI * denom * denom));
}

float	ggx_normal_distribution2(float a_sq, float4 n, float4 m)
{
	float	cos_theta = dot(n, m);
	float	cos_theta_sq = cos_theta * cos_theta;
	float	denom = cos_theta_sq * (a_sq - 1.0f) + 1.0f;
	return ((cos_theta > 0.0f) ? a_sq * M_1_PI_F / (denom * denom) : 0.0f);
}

float4	sample_ggx_distriburion(float4 wi, float cos_theta, float4 *state)
{
	float e1 = GPURnd(state);
	float e2 = GPURnd(state);
	cos_theta = sqrt((1.0f - e1)
					/ (e1 * (cos_theta - 1.0f) + 1.0f));
	float phi = e2 * M_PI_F * 2.0f;
	float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
	float4 u, v, w;
	build_from_w(&u, &v, &w, wi);
	return ((float4)((u * cos(phi) +
					v * sin(phi)) * sin_theta +
					w * cos_theta));
}

//wo from ray
//wi incident direction
t_color	conductor_sample_material(t_material material, t_shade_rec *shade_rec,
								t_color *f, float *pdf, float *weight,
								t_texture_manager texture_manager, float4 *state)
{
	if (dot(shade_rec->normal, shade_rec->ray.direction) > 0.0f)
		shade_rec->normal = -shade_rec->normal;

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * shade_rec->normal;
	float4 wo = -shade_rec->ray.direction;

	shade_rec->ray.direction = sample_ggx_distriburion(
		get_reflected_vector(shade_rec->ray.direction, shade_rec->normal),
		material.exp * material.exp, state);

	float4 h = normalize(wo + shade_rec->ray.direction);

	float ndotwo = dot(shade_rec->normal, wo);
	float ndotwi = dot(shade_rec->normal, shade_rec->ray.direction);
	float hdotwi = dot(h, shade_rec->ray.direction);
	float ndoth = dot(shade_rec->normal, h);
	{
		float fr = fresnel_conductor(hdotwi);
		float d = ggx_normal_distribution(material.exp * material.exp, ndoth);
		float g = ggx_visibility_term(material.exp * material.exp, ndotwi,
													ndotwo);

		*pdf = d * ndoth / (4.0f * hdotwi);
		if (*pdf < 0.05f)
			*f = (t_color){0.0f, 0.0f, 0.0f, 0.0f};
		else
			*f = float_color_multi(fr * d * g / (4.0f * ndotwo),
							get_color(texture_manager, material, shade_rec));
	}
}

float	fresnel_dielectric(float4 wo, float4 m, float eta)
{
	float	result = 1.0f;
	float	cos_theta_wo = dot(wo, m);
	if (cos_theta_wo < 0.0f)
		cos_theta_wo = -cos_theta_wo;
	float	sin_theta_os_squared = eta * eta
								* (1.0f - cos_theta_wo * cos_theta_wo);
	if (sin_theta_os_squared <= 1.0f)
	{
		float cos_theta = sqrt(clamp(1.0f - sin_theta_os_squared, 0.0f, 1.0f));
		float Rs = (cos_theta_wo - eta * cos_theta)
				/ (cos_theta_wo + eta * cos_theta);
		float Rp = (eta * cos_theta_wo - cos_theta)
				/ (eta * cos_theta_wo + cos_theta);
		result = 0.5f * (Rs * Rs + Rp * Rp);
	}
	return (result);
}

float	remap_roughness(float roughness, float ndotwo)
{
	if (ndotwo < 0.0f)
		ndotwo = -ndotwo;
	float alpha = (1.2f - 0.2f * sqrt(ndotwo)) * roughness;
	return (alpha * alpha);
}

float	sqr(float a)
{
	return (a * a);
}

t_color	evaluate_dielectric(t_material material, t_shade_rec *shade_rec,
							t_color *f, float *pdf, float *weight,
							t_texture_manager texture_manager, float4 *state,
							float4 wi)
{
	bool entering_material = dot(shade_rec->normal,
							shade_rec->ray.direction) < 0.0f;
	float4 n = entering_material ? shade_rec->normal : -shade_rec->normal;

	float ndotwo = -dot(n, shade_rec->ray.direction);
	float ndotwi = dot(n, wi);
	bool reflection = ndotwi * ndotwo > 0.0f;

	float eta = entering_material ? (1.0f / material.kt)
									: (material.kt / 1.0f);

	float4 m = normalize(reflection ? (wi - shade_rec->ray.direction)
									: (shade_rec->ray.direction * eta - wi));
	m *= (dot(n, m) < 0.0f) ? -1.0f : 1.0f;

	float MdotI = -dot(m, shade_rec->ray.direction);
	float MdotO = dot(m, wi);
	float NdotM = dot(n, m);
	float alpha = remap_roughness(material.exp, ndotwo);

	float F = fresnel_dielectric(shade_rec->ray.direction, m, eta);
	float D = ggx_normal_distribution2(alpha, n, m);
	float G = ggx_visibility_term2(alpha, shade_rec->ray.direction, wi, n, m);

	if (reflection)
	{
		float J = 1.0f / (4.0f * MdotO);

		shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * m;
		*f = (t_color){1.5f, 1.5f, 1.5f, 0.0f};
		// *f = float_color_multi(D * G * F / (4.0f * ndotwo),
							// (t_color){1.0f, 1.0f, 1.0f, 0.0f});
		*pdf = F * J;
		// *f =
	}
	else
	{
		float J = MdotI / sqr(MdotI * eta + MdotO);

		float value = (1.0f - F) * D * G * MdotI * MdotO / (ndotwo * sqr(MdotI * eta + MdotO));
		if (value < 0.0f)
			value = -value;
		*f = (t_color){1.0f, 1.0f, 1.0f, 0.0f};

		// *f = float_color_multi(value, (t_color){1.0f, 1.0f, 1.0f, 0.0f});
		*pdf = (1.0f - F) * J;
		shade_rec->ray.origin = shade_rec->hit_point - 1e-2f * m;
	}
	*f = float_color_multi(G * MdotI / (ndotwo * NdotM), *f);
	// *pdf *= D * NdotM;
	*pdf = 1.0f;
}

t_color	dielectric_sample_material(t_material material, t_shade_rec *shade_rec,
								t_color *f, float *pdf, float *weight,
								t_texture_manager texture_manager, float4 *state)
{
	bool	entering_material =
		dot(shade_rec->normal, shade_rec->ray.direction) < 0.0f;

	float4	n = entering_material ? shade_rec->normal : -shade_rec->normal;
	float	a = remap_roughness(material.exp, dot(n, shade_rec->ray.direction));
	float4	m = sample_ggx_distriburion(n, a, state);

	float eta_i = entering_material ? 1.0f : material.kt;
	float eta_o = entering_material ? material.kt : 1.0f;
	float eta = eta_i / eta_o;

	float fr = fresnel_dielectric(shade_rec->ray.direction, m, eta);

	float4 wi;
	if (GPURnd(state) > fr) //refraction
	{
		float cos_theta_i = dot(m, -shade_rec->ray.direction);
		float sin_theta_os_squared = (eta * eta)
								* (1.0f - cos_theta_i * cos_theta_i);
		float cosThetaO = sqrt(clamp(1.0f - sin_theta_os_squared, 0.0f, 1.0f));
		wi = normalize(eta * shade_rec->ray.direction +
						m * (eta * cos_theta_i - cosThetaO));

		if (dot(n, shade_rec->ray.direction) * dot(n, wi) <= 0.0f)
		{
			*pdf = 0.0f;
			return *f;
		}
		// shade_rec->ray.origin = shade_rec->hit_point - 1e-4f * n;
	}
	else
	{
		wi = get_reflected_vector(shade_rec->ray.direction, m);

		if (dot(n, shade_rec->ray.direction) * dot(n, wi) >= 0.0f)
		{
			*pdf = 0.0f;
			return (*f);
		}
	}
	evaluate_dielectric(material, shade_rec, f, pdf, weight,
								texture_manager, state,
								wi);
	shade_rec->ray.direction = wi;
}

t_color	plastic_evaluate(t_material material, t_shade_rec *shade_rec,
						t_color *f, float *pdf, float *weight,
						t_texture_manager texture_manager, float4 *state,
						float4 wi)
{
	float NdotI = -dot(shade_rec->normal, shade_rec->ray.direction);
	float NdotO = dot(shade_rec->normal, wi);
	float4 m = normalize(wi - shade_rec->ray.direction);
	float NdotM = dot(shade_rec->normal, m);
	float MdotO = dot(m, wi);

	float a = material.exp * material.exp;
	float F = fresnel_dielectric(shade_rec->ray.direction, m,
								material.kr);
	float D = ggx_normal_distribution2(a, shade_rec->normal, m);
	float G = ggx_visibility_term2(a, shade_rec->ray.direction, wi,
									 shade_rec->normal, m);
	float J = 1.0f / (4.0 * MdotO);;

	t_color c = get_color(texture_manager, material, shade_rec);

	*f = color_sum(float_color_multi(M_1_PI_F * NdotO * (1.0f - F), c),
					float_color_multi(F * D * G / (4.0 * NdotI) * material.kr,
									(t_color){1.0, 1.0f, 1.0f, 0.0f}));

	// *pdf = 1.0f;
	*pdf = M_1_PI_F * NdotO * (1.0f - F) + D * NdotM * J * F;

	shade_rec->ray.origin = shade_rec->hit_point + 1e-2f * m;
	shade_rec->ray.direction = wi;
}


//todo: reverse normal
t_color	plastic_sample_material(t_material material, t_shade_rec *shade_rec,
								t_color *f, float *pdf, float *weight,
								t_texture_manager texture_manager, float4 *state)
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
		float4 u, v, w;

		build_from_w(&u, &v, &w, shade_rec->normal);
		wi = local_dir(&u, &v, &w, random_cosine_direction(state));
	}

	plastic_evaluate(material, shade_rec, f, pdf, weight,
					texture_manager, state, wi);
}

/* sample f*/
t_color	sample_material(t_material material, t_shade_rec *shade_rec,
						t_color *f, float *pdf, float *weight,
						t_texture_manager texture_manager,
						uint2 *seed, float4 *state)
{
	if (material.type == matte || material.type == phong)
	{
		return (matte_sample_material(material, shade_rec, f, pdf, weight,
									texture_manager, state));
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
		return (plastic_sample_material(material, shade_rec, f, pdf, weight,
										texture_manager, state));
	}
	else if (material.type == dielectric)
	{
		return (dielectric_sample_material(material, shade_rec, f, pdf, weight,
											texture_manager, state));
	}
	else if(material.type == emissive)
	{
		*pdf = 0.0f;
		*f = float_color_multi(material.ls, (t_color){1.0f, 1.0f, 1.0f, 0.0f});
		return (*f);
	}
	*pdf = 0.0f;
	return ((t_color){ 0.0f, 0.0f, 0.0f, 0.0f });
}


/* integrator */
t_color	trace(t_ray ray, t_scene scene, t_rt_options options,
			t_sampler_manager sampler_manager,
			uint2 *seed, float4 *state)
{
	t_color	color = (t_color){ .r = 0.0f, .g = 0.0f, .b = 0.0f };

	t_color	beta = (t_color){ .r = 1.0f, .g = 1.0f, .b = 1.0f };

	t_shade_rec	shade_rec;;;
	shade_rec.ray = ray;

	float	material_pdf = 1.0f;
	float	light_pdf = 1.0f;

	char	depth = 0;

	bool	specular_hit = false;

	while (depth < options.depth)
	{
		if (scene_intersection(scene, ray, &shade_rec))
		{

			t_instance instance = _get_instance();
			t_material material = _get_instance_material();

			if (options.strategy == 0)
				color = color_sum(color,
							color_multi(beta,
									area_light_shade(scene,
													sampler_manager,
													material,
													shade_rec,
													options,
													seed)));
			else if (options.strategy == 1)
				color = color_sum(color,
							color_multi(beta,
									sample_light(material, shade_rec,  scene,
												sampler_manager, options, seed,
												state)));

			if (material_pdf == 0.0f)
				break;

			t_color	f;
			float	pdf;
			float	weight;
			float	bsdf;;

			/* scatter */
			sample_material(material, &shade_rec, &f, &pdf, &weight,
								scene.instance_manager.tex_mngr, seed, state);

			if (is_black(f))
					break;
			if (pdf <= 0.01f)
			{
				if (!is_black(f))
					color = color_sum(color_multi(beta, f), color);
				break;
			}

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
