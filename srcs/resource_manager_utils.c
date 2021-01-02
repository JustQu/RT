/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:41:38 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/21 17:32:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_manager.h"
#include "instance_manager.h"
#include "sampler_manager.h"
#include "vector.h"
#include "utils.h"
#include "rt_error.h"
#include "math.h"

static void		scan_instance_01(t_res_mngr *const mngr, t_parsed_info asset)
{
	if (mngr->info.type == cylinder)
	{
		mngr->info.scaling.x *= mngr->info.r;
		mngr->info.scaling.y *= mngr->info.r;
		mngr->info.r = 1.0f;
	}
	mngr->info.r2 = asset.data.object.r2;
	if (mngr->info.type == cone)
		mngr->info.r2 = powf(tanf(asset.data.object.r2 * DEG2RAD), 2.0f) + 1.0f;
	mngr->info.v1 = asset.data.object.vector1;
	mngr->info.v2 = asset.data.object.vector2;
	if (mngr->info.type == rectangle)
	{
		mngr->info.v1 = (mngr->info.v1);
		mngr->info.v2 = (mngr->info.v2);
	}
}

void			scan_instance(t_res_mngr *const mngr, t_parsed_info asset)
{
	mngr->info.type = asset.data.object.type;
	mngr->info.origin = asset.data.object.origin;
	mngr->info.rotation = asset.data.object.rotation;
	mngr->info.scaling = asset.data.object.scaling;
	mngr->info.material = asset.data.object.material;
	mngr->info.texture = asset.data.object.texture;
	mngr->info.height = asset.data.object.maxm;
	mngr->info.r = asset.data.object.r;
	mngr->info.boolean = asset.data.object.boolean;
	if (mngr->info.type == sphere)
	{
		mngr->info.scaling.x *= mngr->info.r;
		mngr->info.scaling.y *= mngr->info.r;
		mngr->info.scaling.z *= mngr->info.r;
		mngr->info.r = 1.0f;
	}
	scan_instance_01(mngr, asset);
}

void			add_parsed_asset(t_res_mngr *const mngr, t_parsed_info asset)
{
	if (asset.type == object)
	{
		scan_instance(mngr, asset);
		if (mngr->info.material.type == emissive)
		{
			add_emissive_instance(mngr, mngr->info);
		}
		else
		{
			add_instance(mngr, &mngr->scene->instance_mngr, mngr->info);
		}
	}
	else if (asset.type == light)
	{
		add_parsed_light(&mngr->scene->light_manager, asset.data.light);
	}
}

/*
** @brief Get the instance info object
** @todo: check array boundaries
** @param mngr
** @param id
** @return **** t_instance_info
*/

t_instance_info	get_instance_info(t_res_mngr *const mngr, t_u32 id)
{
	t_instance			instance;
	t_instance_extra	extra;

	instance = mngr->scene->instance_mngr.instances[
									id % mngr->scene->instance_mngr.ninstances];
	extra = mngr->scene->instance_mngr.extra[
									id % mngr->scene->instance_mngr.ninstances];
	if (instance.type == triangle)
		return (get_triangle_info(mngr, instance, extra));
	else
		return (get_object_info(mngr, instance, extra));
}

t_light			get_light_info(t_res_mngr *const mngr, t_u32 id)
{
	t_light light;

	light = mngr->scene->light_manager.lights[
									id % mngr->scene->light_manager.nlights];
	return (light);
}
