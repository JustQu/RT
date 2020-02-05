/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:11:29 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:10:57 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**vec3 dot product
*/

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/*
**cross product of two vector
**(u2.v3 - u3.v2, u3.v1 - u1.v3, u1.v2 - u2.v1)
*/

void	vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
}

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/

void	vec3_scale(t_vec3 v, float s, t_vec3 dest)
{
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
	dest[2] = v[2] * s;
}

/*
**multiply two vector (component-wise multiplication)
*/

void	vec3_mul(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
	dest[2] = a[2] * b[2];
}

/*
**project a vector onto b vector
*/

void	vec3_proj(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	vec3_scale(b, vec3_dot(a, b) / vec3_norm2(b), dest);
}
