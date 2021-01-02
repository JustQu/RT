/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:55:21 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/19 23:46:59 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_manager.h"
#include "instance_manager.h"
#include "sampler_manager.h"
#include "vector.h"
#include "utils.h"
#include "rt_error.h"
#include "math.h"

/*
** @brief Create inverse transformation matrix for object
** 1) scaling
** 2) rotation
** 3) translation
** @param object_info
** @return ** t_matrix
*/

t_matrix		create_inv_transformation_matrix(t_instance_info info)
{
	t_matrix	m;

	m = IDENTITY_MATRIX;
	m = mul_matrix(m, get_inverse_scale_matrix(info.scaling));
	m = mul_matrix(m, get_inverse_rotation_matrix(info.rotation));
	m = mul_matrix(m, get_inverse_translation_matrix(info.origin));
	return (m);
}

/*
** todo: malloc check
*/

int				add_instance(t_res_mngr *res_mngr,
							t_instance_manager *mngr, t_instance_info data)
{
	t_instance	new;

	if (mngr->instances_malloc_size <
		(mngr->ninstances + 1) * sizeof(*mngr->instances))
	{
		mngr->instances = ft_realloc(mngr->instances,
			mngr->instances_malloc_size, mngr->instances_malloc_size * 2);
		rt_is_dead(system_err, system_malloc_error, !mngr->instances, "");
		mngr->instances_malloc_size *= 2;
		mngr->extra = ft_realloc(mngr->extra, mngr->extra_size,
								mngr->extra_size * 2);
		mngr->extra_size *= 2;
	}
	new.type = data.type;
	new.material = data.material;
	new.object_id = add_object(mngr, data);
	new.matrix_id = add_matrix(mngr, create_inv_transformation_matrix(data));
	new.material.texture_id = add_texture(
			&res_mngr->scene->instance_mngr.texture_manager, data.texture);
	mngr->instances[mngr->ninstances] = new;
	mngr->extra[mngr->ninstances].aabb = compute_aabb(data);
	mngr->extra[mngr->ninstances].origin = data.origin;
	mngr->extra[mngr->ninstances].rotation = data.rotation;
	mngr->extra[mngr->ninstances].scaling = data.scaling;
	return (++mngr->ninstances - 1);
}

float			compute_area(t_instance_info info)
{
	float	s;

	s = 0.0f;
	if (info.type == rectangle)
	{
		s = info.r * info.r2 * info.scaling.x * info.scaling.z;
	}
	return (s);
}

void			add_emissive_instance(t_res_mngr *mngr, t_instance_info data)
{
	int				i;
	int				j;
	t_parsed_light	l;

	if (data.material.type == emissive
		&& data.type == rectangle)
	{
		i = add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
		set_sampler(&mngr->scene->instance_mngr, i,
					new_sampler(mngr->sampler_manager, pure_random,
								1024, DEFAULT_SAMPLES));
		l.ls = data.material.ls;
		l.color = data.texture.data.solid.color;
		l.type = area;
		l.pdf = 1.0f / compute_area(data);
		j = add_parsed_light(&mngr->scene->light_manager, l);
		mngr->scene->light_manager.lights[j].object_id = i;
		mngr->scene->light_manager.lights[j].matrix =
										get_transformation_matrix(mngr->info);
	}
	else
	{
		data.material.type = matte;
		add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
	}
}

int				init_resource_manager(t_res_mngr *resource_manager,
										t_rt *rt)
{
	resource_manager->scene = &rt->scene;
	resource_manager->sampler_manager = &rt->sampler_manager;
	resource_manager->rt_options = &rt->options;
	return (SUCCESS);
}
