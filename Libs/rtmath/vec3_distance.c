/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:17:00 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:23:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**find center point of two vector
*/

void	vec3_center(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	vec3_sum(a, b, dest);
	vec3_scale(dest, 0.5f, dest);
}

/*
**squared distance between two vectors
*/

float	t_vec3_distance2(t_vec3 a, t_vec3 b)
{
	return (pow2(b[0] - a[0])
			+ pow2(b[1] - a[1])
			+ pow2(b[2] - a[2]));
}

/*
**distance beween two vector
*/

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (sqrtf(t_vec3_distance2(a, b)));
}

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t	interpolant (amount) clamped between 0 and 1
*/

void	vec3_lerp(t_vec3 from, t_vec3 to, float t, t_vec3 dest)
{
	t_vec3 s;
	t_vec3 v;

	vec3_broadcast(clamp_zo(t), s);
	vec3_sub(to, from, v);
	vec3_mul(s, v, v);
	vec3_sum(from, v, dest);
}
