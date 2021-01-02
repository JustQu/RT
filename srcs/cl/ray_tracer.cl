float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = l - 2 * dot(l, n) * n;
	return normalize(r);
}

inline t_material	get_instance_material(t_instance_manager instance_manager,
											t_instance instance)
{
	return (instance.material);
}

inline t_instance	get_instance(t_instance_manager instance_manager, int id)
{
	return instance_manager.instances[id];
}

inline t_matrix	get_instance_matrix(t_instance_manager instance_manager,
									t_instance	instance)
{
	return (instance_manager.matrices[instance.matrix_id]);
}

inline t_obj	get_object_info(t_instance_manager instance_manager,
									t_instance instance)
{
	return (instance_manager.objects[instance.object_id]);
}

inline t_triangle	get_triangle_info(t_instance_manager instance_manager,
										t_instance instance)
{
	return (instance_manager.triangles[instance.object_id]);
}

bool	bvh_intersection(t_scene scene, t_shade_rec *shade_rec)
{
	int				node_id = 0;

	shade_rec->id = -1;

	float	tmin = K_HUGE_VALUE;
	while (node_id != -1)
	{
		t_bvh_node current_node = scene.bvh[node_id];

		if (bbox_intersection(shade_rec->ray, current_node.aabb))
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
								&tmin, shade_rec))
				{
					shade_rec->id = current_node.instance_id;

					shade_rec->hit_point = shade_rec->ray.direction * tmin + shade_rec->ray.origin;
				}
				node_id = current_node.next;
			}
		}
		else
		{
			node_id = current_node.next;
		}
	}
	return (shade_rec->id > -1);
}

bool	scene_intersection(t_scene scene, t_ray ray, t_shade_rec *shade_rec)
{
	bool ret = bvh_intersection(scene, shade_rec);

	return (ret);
}

#define maximum_tree_depth 16

t_color	ray_cast(t_ray ray, t_scene scene, t_rt_options options,
				t_sampler_manager sampler_manager, uint2 *seed)
{
	int			local_id = get_local_id(0);
	t_shade_rec	shade_rec;

	/* computed color */
	t_color		color = options.background_color;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;

	float		color_coef = 1.0f;
	t_color		clr_coef;
	clr_coef.r = 1.0f;
	clr_coef.g = 1.0f;
	clr_coef.b = 1.0f;

	/* material of hit object*/
	t_material	instance_material;

	bool		continue_loop = true;
	uchar		tree_depth = 0;

	while (continue_loop)
	{
		tree_depth++;
		shade_rec.ray = ray;
		if (scene_intersection(scene, ray, &shade_rec))
		{
			t_instance	instance = scene.instance_manager.instances[shade_rec.id];

			/* if normal is not directed to us then we reverse normal*/
			// shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
				// shade_rec.normal : -shade_rec.normal;
			if (dot(shade_rec.normal, shade_rec.ray.direction) > 0.0f)
				shade_rec.normal = -shade_rec.normal;

			instance_material = get_instance_material(scene.instance_manager,
														instance);

			/* shade material at hit point and accumulate color */
			color = color_sum(color,
							float_color_multi(color_coef,
											shade_material(scene,
															sampler_manager,
															instance_material,
															shade_rec, options,
															seed)));

			continue_loop = false;
		}
		else /* no hit */
		{
			continue_loop = false;
		}
	};
	return (color);
}
