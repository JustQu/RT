/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:14:22 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/17 10:12:48 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	copyClfloat3(cl_float3 *src, cl_float3 *dst)
{
	dst->s[0] = src->s[0];
	dst->s[1] = src->s[1];
	dst->s[2] = src->s[2];
	dst->s[3] = src->s[3];
}

float	dotClfloat3(cl_float *a, cl_float *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

float	norm2Clfloat3(cl_float3 *v)
{
	return (vec3_dot(v, v));
}

float	normClfloat3(cl_float3 *v)
{
	return (sqrtf(vec3_norm2(v)));
}

void	normalizeClfloat3(cl_float3 *v)
{
	float norm;

	norm = vec3_norm(v);
	if (norm == 0.0f)
	{
		v->s[0] = 0.0f;
		v->s[1] = 0.0f;
		v->s[2] = 0.0f;
		return ;
	}
	vec3_scale(v, 1.0f / norm, v);
}