/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:00:00 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:11:22 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

/*
**vec4 dot product
*/

float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
}

/*
**multiply two vector (component-wise multuplication)
*/

void	vec4_mul(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
	dest[3] = a[3] * b[3];
}

/*
**mul vector with scalar and add result to sum
*/

void	vec4_muladds(t_vec4 a, float s, t_vec4 dest)
{
	dest[0] += a[0] * s;
	dest[1] += a[1] * s;
	dest[2] += a[2] * s;
	dest[3] += a[3] * s;
}

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/

void	vec4_scale(t_vec4 a, float s, t_vec4 dest)
{
	dest[0] = a[0] * s;
	dest[1] = a[1] * s;
	dest[2] = a[2] * s;
	dest[3] = a[3] * s;
}

/*
**make vec4 vector scale as specified: result = unit(v) * s
*/

void	vec4_scale_as(t_vec4 v, float s, t_vec4 dest)
{
	float	norm;

	norm = vec4_norm(v);
	if (norm == 0.0f)
	{
		vec4_zero(dest);
		return ;
	}
	vec4_scale(v, s / norm, dest);
}
