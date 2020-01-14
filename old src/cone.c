/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:38:06 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 16:49:07 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool	cone_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4	tmp;
	t_vec4	coef;
	t_cone	*cn;

	cn = (t_cone *)obj->data;
	vec3_sub(ray->point, obj->c_s, tmp);
	coef[a] = vec3_dot(ray->vec, ray->vec) - cn->k2
	* pow2(vec3_dot(ray->vec, cn->dir));
	coef[b] = vec3_dot(ray->vec, tmp) - cn->k2 *
	vec3_dot(ray->vec, cn->dir) * vec3_dot(tmp, cn->dir);
	coef[b] *= 2.0f;
	coef[c] = vec3_dot(tmp, tmp) - cn->k2 * (pow2(vec3_dot(tmp, cn->dir)));
	coef[d] = pow2(coef[b]) - 4.0f * coef[a] * coef[c];
	if (coef[d] >= 0.0f)
	{
		obj->t = (-coef[b] - sqrtf(coef[d])) * 0.5f / coef[a];
		if (obj->t <= 0.0f)
			obj->t = (-coef[b] - sqrtf(coef[d])) * 0.5f / coef[a];
		return (obj->t >= 0.0f);
	}
	return (FALSE);
}
