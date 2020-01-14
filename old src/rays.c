/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 14:57:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 18:10:11 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		trace_ray(t_param *p, t_ray *ray)
{
	t_obj	*obj;
	t_color	color;
	int		i;

	i = -1;
	color.color = BACKGROUND;
	obj = get_intersection(p->world.objs, p->world.nobjs, ray);
	if (obj)
	{
		return (color = get_point_color(&(p->world), obj, ray, i));
	}
	return (color);
}

t_ray		cast_shadow_ray(t_vec3 start, t_light_source *light)
{
	t_ray	shadow_ray;

	vec3_copy(start, shadow_ray.point);
	vec3_sub(light->c_s, start, shadow_ray.vec);
	normalize(shadow_ray.vec);
	return (shadow_ray);
}
