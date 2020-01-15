/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:36:36 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bool	plane_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec2	coefs;
	t_plane pl;
	float	denom;

	pl = *(t_plane *)obj->data;
	vec3_sub(obj->c_s, ray->point, tmp);
	denom = vec3_dot(pl.nv, ray->vec);
	coefs[a] = -vec3_dot(pl.nv, tmp);
	coefs[b] = vec3_dot(pl.nv, ray->vec);
	if (denom > 1e-6f)
	{
		vec3_sub(obj->c_s, ray->point, tmp);
		obj->t = vec3_dot(tmp, pl.nv) / denom;
		return (obj->t >= 0.0f);
		if ((obj->t = coefs[a] / coefs[b]) >= 0.0f)
			return (TRUE);
		if (coefs[b] < 0.0f)
		{
			obj->t = -obj->t;
			return (TRUE);
		}
		return (FALSE);
	}
	return (FALSE);
}
