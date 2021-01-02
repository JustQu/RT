float4	get_ambient_occluder_direction(t_ambient_occluder ambient_occluder,
										t_sampler_manager sampler_manager,
										t_sampler *sampler,
										uint2 *seed)
{
	float3 sp = sample_hemisphere(sampler, sampler_manager.hemisphere_samples, seed);
	return (sp.x * ambient_occluder.u
		+ sp.y * ambient_occluder.v
		+ sp.z * ambient_occluder.w);
}

bool	in_shadow(t_ray shadow_ray, t_scene scene)
{
	float	t;
	float	tmin = 100000;
	int			node_id = 0;
	t_bvh_node	current_node;

	t_shade_rec	sr;
	sr.ray = shadow_ray;

	while (node_id != -1)
	{
		current_node = scene.bvh[node_id];

		if (bbox_intersection(shadow_ray, current_node.aabb))
		{
			if (current_node.instance_id == -1)
			{
				node_id++;
			}
			else /* leaf node*/
			{
				t_instance instance = get_instance(scene.instance_manager,
													current_node.instance_id);
				if (instance_hit(scene.instance_manager, instance,
								&tmin, &sr))
				{
					return (true);
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}
	return (false);
}

t_color	ambient_occlusion_l(t_scene scene,
							t_sampler_manager sampler_manager,
							t_sampler *sampler,
							t_shade_rec shade_rec,
							uint2 *seed)
{
	t_color	color = {1.0f, 1.0f, 1.0f, 0.0f};

	scene.ambient_occluder.w = shade_rec.normal;
	scene.ambient_occluder.v = normalize(cross(scene.ambient_occluder.w, (float4)(0.0072f, 1.0f, 0.0034f, 0.0f)));
	scene.ambient_occluder.u = cross(scene.ambient_occluder.v, scene.ambient_occluder.w);

	t_ray shadow_ray;
	shadow_ray.origin = shade_rec.hit_point + 1e-3f * shade_rec.normal;
	shadow_ray.direction = get_ambient_occluder_direction(scene.ambient_occluder, sampler_manager, sampler, seed);
	// color = float_color_multi(scene.ambient_occluder.ls, scene.ambient_occluder.color);
	if (in_shadow(shadow_ray, scene))
		color = float_color_multi(0.00f, color);
	else
		color = float_color_multi(scene.ambient_occluder.ls,
									scene.ambient_occluder.color);

	return (color);
}
