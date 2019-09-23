/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:09:22 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:20:47 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
** angle between two vector
*/

/*
** maybe compiler generate approximation instruction (rcp)
*/

float	vec3_angle(t_vec3 a, t_vec3 b)
{
	float	norm;
	float	dot;

	norm = 1.0f / (vec3_norm(a) * vec3_norm(b));
	dot = vec3_dot(a, b) * norm;
	if (dot > 1.0f)
		return (0.0f);
	else if (dot < -1.0f)
		return (RTM_PI);
	return (acosf(dot));
}

/*
** rotate vec3 around axis by angle using Rodrigues' rotation formula
** Right Hand, Rodrigues' rotation formula:
** v = v*cos(t) + (kxv)sin(t) + k*(k.v)(1 - cos(t))
*/

void	vec3_rotate(t_vec3 v, float angle, t_vec3 axis)
{
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	k;
	float	c;
	float	s;

	c = cosf(angle);
	s = sinf(angle);
	vec3_normalize_to(axis, k);
	vec3_scale(v, c, v1);
	vec3_cross(k, v, v2);
	vec3_scale(v2, s, v2);
	vec3_sum(v1, v2, v1);
	vec3_scale(k, vec3_dot(k, v) * (1.0f - c), v2);
	vec3_sum(v1, v2, v);
}

/*
** apply rotation matrix to vector
*/

void	vec3_rotate_m4(t_mat4 m, t_vec3 v, t_vec3 dest)
{
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;
	t_vec4	res;

	vec4_normalize_to(m[0], x);
	vec4_normalize_to(m[1], y);
	vec4_normalize_to(m[2], z);
	vec4_scale(x, v[0], res);
	vec4_muladds(y, v[1], res);
	vec4_muladds(z, v[2], res);
	vec4_to_vec3(res, dest);
}

void	vec3_rotate_m3(t_mat3 m, t_vec3 v, t_vec3 dest)
{
	t_vec4	res;
	t_vec4	x;
	t_vec4	y;
	t_vec4	z;

	vec3_to_vec4(m[0], 0.0f, x);
	vec3_to_vec4(m[1], 0.0f, y);
	vec3_to_vec4(m[2], 0.0f, z);
	vec4_normalize(x);
	vec4_normalize(y);
	vec4_normalize(z);
	vec4_scale(x, v[0], res);
	vec4_muladds(y, v[1], res);
	vec4_muladds(z, v[2], res);
	vec4_to_vec3(res, dest);
}
