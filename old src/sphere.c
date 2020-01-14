/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 13:52:46 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:10:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool	sphere_intersection(t_obj *obj, t_ray *ray)
{
	t_vec4		tmp;
	t_vec4		coefs;
	t_sphere	sp;
	float		t;

	sp = *(t_sphere *)(obj->data);
	vec3_sub(ray->point, obj->c_s, tmp);
	coefs[a] = vec3_norm2(ray->vec);
	coefs[b] = 2.0f * vec3_dot(ray->vec, tmp);
	coefs[c] = vec3_norm2(tmp) - sp.radius * sp.radius;
	coefs[d] = coefs[b] * coefs[b] - 4.0f * coefs[a] * coefs[c];
	if (coefs[d] >= 0.0f)
	{
		coefs[a] *= 2.0f;
		coefs[d] = sqrtf(coefs[d]);
		t = (-coefs[b] - coefs[d]) / coefs[a];
		if (t < 0.0f)
			if ((t = (-coefs[b] - coefs[d]) / coefs[a]) < 0.0f)
				return (FALSE);
		obj->t = t;
		return (TRUE);
	}
	return (FALSE);
}
