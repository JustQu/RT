/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:19:57 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:18:56 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		world_to_camera(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->world.nobjs)
	{
		vec3_copy((p->world.objs + i)->origin, (p->world.objs + i)->c_s);
		vec3_sub((p->world.objs + i)->c_s,
		p->camera.origin, (p->world.objs + i)->c_s);
	}
	i = -1;
	while (++i < p->world.nlights)
	{
		vec3_copy((p->world.lights + i)->origin, (p->world.lights + i)->c_s);
		vec3_sub((p->world.lights + i)->c_s,
		p->camera.origin, (p->world.lights + i)->c_s);
	}
	vec3_zero(p->camera.origin);
}
