/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:22:40 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:54:56 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bool.h"
#include "instance_manager.h"
#include "utils.h"
#include "rt_error.h"

/*
** @brief adding new traingle with triangle info
** @todo: normal
** @param mngr
** @param triangle_info
** @return ** int
*/

int		add_triangle(t_instance_manager *mngr, t_instance_info triangle_info)
{
	t_triangle	triangle;

	if (mngr->triangles_malloc_size
		< (mngr->ntriangles + 1) * sizeof(t_triangle))
	{
		mngr->triangles = (t_triangle *)ft_realloc(mngr->triangles,
			mngr->triangles_malloc_size, mngr->triangles_malloc_size * 2);
		rt_is_dead(system_err, system_malloc_error, !mngr->triangles, "");
		mngr->triangles_malloc_size *= 2;
	}
	triangle.vertex1 = (cl_float4){{0.0f, 0.0f, 0.0f, 0.0f}};
	triangle.vector1 = triangle_info.v1;
	triangle.vector2 = triangle_info.v2;
	mngr->triangles[mngr->ntriangles] = triangle;
	return (++mngr->ntriangles - 1);
}

/*
** @brief
** @todo: mesh object
** @param mngr
** @param object_info
** @return ** int
*/

int		add_obj(t_instance_manager *mngr, t_instance_info object_info)
{
	t_obj	object;

	if (mngr->objects_malloc_size < (mngr->nobjects + 1) * sizeof(t_obj))
	{
		mngr->objects = (t_obj *)ft_realloc(mngr->objects,
			mngr->objects_malloc_size, mngr->objects_malloc_size * 2);
		rt_is_dead(system_err, system_malloc_error, !mngr->objects, "");
		mngr->objects_malloc_size *= 2;
	}
	object.minm = 0.0f;
	object.maxm = object_info.height;
	object.boolean = object_info.boolean;
	object.origin = (cl_float4){{0.0f, 0.0f, 0.0f, 0.0f}};
	object.r = object_info.r;
	object.r2 = object_info.r2;
	object.direction = object_info.v1;
	object.dir2 = object_info.v2;
	mngr->objects[mngr->nobjects] = object;
	return (++mngr->nobjects - 1);
}

/*
** @brief Добавить новый объект типа type
** Возвращает id объекта
** @param instance_manager
** @param object_info
** @return ** int
*/

int		add_object(t_instance_manager *mngr, t_instance_info object_info)
{
	if (object_info.type == triangle)
	{
		return (add_triangle(mngr, object_info));
	}
	else
	{
		return (add_obj(mngr, object_info));
	}
}

void	set_sampler(t_instance_manager *instance_manager,
					int id,
					int sampler_id)
{
	instance_manager->objects[
		instance_manager->instances[id].object_id].sampler_id = sampler_id;
}
