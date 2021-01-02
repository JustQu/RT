float4	sample_object(t_instance_manager instance_manager,
						t_sampler_manager sampler_manager,
						t_instance instance,
						t_obj object,
						t_matrix matrix,
						// t_sampler *sampler,
						uint2 *seed)
{
	t_sampler	sampler = get_sampler(sampler_manager, object.sampler_id);

	if (instance.type == rectangle)
	{
		//todo: pass depth
		sampler.jump = get_global_id(0);
		sampler.jump = (random(seed) % sampler.num_sets)
					* sampler.num_samples;
		sampler.count = get_global_id(0) + random(seed);

		float2 sp = sample_unit_square(&sampler,
									sampler_manager.samples, seed);
		float4 point = object.origin
					+ sp.x * object.direction * object.r
					+ sp.y * object.dir2 * object.r2;
		return (point);
	}
}

float4	get_light_direction(t_light light, t_shade_rec shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec.hit_point));
	else if (light.type == directional)
		return -normalize(light.direction);
	else
		return ((float4)(0.0f));
}

float4	get_light_direction2(t_scene scene, t_light *light,
							t_shade_rec shade_rec,
							t_sampler_manager sampler_manager, uint2 *seed)
{
	if (light->type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light->type == point)
		return (normalize(light->origin - shade_rec.hit_point));
	else if (light->type == directional)
		return -normalize(light->direction);
	else if (light->type == area)
	{
		t_instance	instance = get_instance(scene.instance_manager,
											light->object_id);
		t_obj		obj = get_object_info(scene.instance_manager,
									instance);
		t_matrix	matrix = get_instance_matrix(scene.instance_manager,
												instance);

		if (instance.type == rectangle)
		{
			//NOTE: origin is sample point
			light->origin = sample_object(scene.instance_manager,
												sampler_manager,
												instance,
												obj,
												matrix,
												seed);
			light->origin = point_matrix_mul(light->origin, light->matrix);
			//NOTE:store light normal in light direction
			light->direction = vector_matrix_mul(
								(float4)(0.0f, -1.0f, 0.0f, 0.0f),
								light->matrix);
			//NOTE: also compute inverse area which is pdf
			// light->pdf = 1.0f / (length(obj.direction) * length(obj.dir2) * obj.r * obj.r2);
			return (normalize(light->origin - shade_rec.hit_point));
		}
	}
}

t_color	get_light_radiance(t_light light)
{
	t_color	color;

	if (light.type == ambient)
	{
		color.r = light.color.r * light.ls;
		color.g = light.color.g * light.ls;
		color.b = light.color.b * light.ls;
		return (color);
	}
}

t_color	light_l(t_light light, float4 wi)
{
	t_color	color;


	if (light.type == area)
	{
		float ndotd = dot(-light.direction, wi);

		if (ndotd > 0.0f)
		{
			return (float_color_multi(light.ls, light.color));
		}
		else
		{
			return ((t_color){ 0.0f, 0.0f, 0.0f, 0.0f });
		}
	}
	else
	{
		color = float_color_multi(light.ls, light.color);
	}
	return (color);
}

float	light_g(t_light light, float4 wi, t_shade_rec shade_rec)
{
	float g = 1.0f;
	if (light.type == area)
	{
		//NOTE: direction is normal in this case
		float ndotd = dot(-light.direction, wi);
		float d2 = distance(light.origin, shade_rec.hit_point);
		d2 = 1.0f / d2;
		g = ndotd * d2 * d2;
	}
	return g;
}

float	light_pdf(t_light light)
{
	float	pdf = 1.0f;

	if (light.type == area)
	{
		pdf = light.pdf;
	}
	return (pdf);
}
