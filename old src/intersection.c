/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 14:12:29 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 17:24:57 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_intersect(t_obj *obj, t_ray *ray)
{
	t_bool	is_hit;

	is_hit = FALSE;
	if (obj->type == sphere)
		is_hit = sphere_intersection(obj, ray);
	else if (obj->type == plane)
		is_hit = plane_intersection(obj, ray);
	else if (obj->type == cone)
		is_hit = cone_intersection(obj, ray);
	else if (obj->type == cylinder)
		is_hit = cylinder_intersection(obj, ray);
	return (is_hit);
}

void		get_hit_point(t_obj *obj, t_ray *ray)
{
	vec3_scale(ray->vec, obj->t, obj->hit_point);
	vec3_sum(obj->hit_point, ray->point, obj->hit_point);
}

t_obj		*get_intersection(t_obj *objs, int nobjs, t_ray *ray)
{
	int		i;
	int		hit_id;
	float	hit_distance;

	i = -1;
	hit_id = -1;
	hit_distance = __FLT_MAX__;
	while (++i < nobjs)
	{
		if (is_intersect(objs + i, ray) && (objs + i)->t < hit_distance)
		{
			if (hit_id != -1)
				(objs + hit_id)->t = INFINITY;
			hit_distance = (objs + i)->t;
			hit_id = i;
		}
	}
	if (hit_id != -1)
	{
		get_hit_point(objs + hit_id, ray);
		get_surface_normal(objs + hit_id);
		(objs + hit_id)->t = INFINITY;
	}
	return ((hit_id != -1 && hit_distance < 1000.0f) ? objs + hit_id : NULL);
}
