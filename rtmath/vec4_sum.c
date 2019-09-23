/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_sum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:02:49 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:11:06 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"
#include "utils.h"
#include "math.h"

/*
**add b vector to a vector store result in dest
*/

void	vec4_sum(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	dest[3] = a[3] + b[3];
}

/*
**add scalar to v vector store result in dest (d = v + vec(s))
*/

void	vec4_adds(t_vec4 v, float s, t_vec4 dest)
{
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
	dest[3] = v[3] + s;
}

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t - interpolant (amount) clamped between 0 and 1
*/

void	vec4_lerp(t_vec4 from, t_vec4 to, float t, t_vec4 dest)
{
	t_vec4 s;
	t_vec4 v;

	vec4_broadcast(clamp_zo(t), s);
	vec4_sub(to, from, v);
	vec4_mul(s, v, v);
	vec4_sum(from, v, dest);
}

/*
**distance between two vectors
*/

float	vec4_distance(t_vec4 a, t_vec4 b)
{
	return (sqrtf(pow2(b[0] - a[0])
				+ pow2(b[1] - a[1])
				+ pow2(b[2] - a[2])
				+ pow2(b[3] - a[3])));
}
