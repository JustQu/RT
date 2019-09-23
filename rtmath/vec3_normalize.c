/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:06:32 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:22:15 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**norm (magnitude of vec3)
*/

float	vec3_norm(t_vec3 v)
{
	return (sqrtf(vec3_norm2(v)));
}

/*
**norm * norm (magnitude) of vec
*/

float	vec3_norm2(t_vec3 v)
{
	return (vec3_dot(v, v));
}

/*
**normalize vec3 and store result in same vec
*/

void	vec3_normalize(t_vec3 v)
{
	float norm;

	norm = vec3_norm(v);
	if (norm == 0.0f)
	{
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		return ;
	}
	vec3_scale(v, 1.0f / norm, v);
}

/*
**normalize vec3 and store result in dest
*/

void	vec3_normalize_to(t_vec3 v, t_vec3 dest)
{
	float norm;

	norm = vec3_norm(v);
	if (norm == 0.0f)
	{
		vec3_zero(dest);
		return ;
	}
	vec3_scale(v, 1.0f / norm, dest);
}
