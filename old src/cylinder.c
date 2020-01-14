/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:34:46 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 17:12:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool		cylinder_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_cylinder	cl;

	cl = *(t_cylinder *)obj->data;
	vec3_sub(ray->point, obj->c_s, tmp);
	coefs[a] = vec3_norm2(ray->vec) - pow2(vec3_dot(ray->vec, cl.dir));
	coefs[b] = vec3_dot(ray->vec, tmp) - vec3_dot(ray->vec, cl.dir)
	* vec3_dot(tmp, cl.dir);
	coefs[b] *= 2.0f;
	coefs[c] = vec3_norm2(tmp) - pow2(vec3_dot(tmp, cl.dir))
	- cl.radius * cl.radius;
	coefs[d] = pow2(coefs[b]) - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		coefs[a] *= 2.0f;
		coefs[d] = sqrtf(coefs[d]);
		obj->t = (-coefs[b] - coefs[d]) / coefs[a];
		if (obj->t >= 0.0f)
			return (TRUE);
	}
	return (FALSE);
}
