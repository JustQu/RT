/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:14:36 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:28:47 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "math.h"
#include "matrix.h"

/*
** @brief Normalize vector
**
** @param vec
** @return ** cl_float4
*/

cl_float4	norm4(cl_float4 vec)
{
	float	magnitude;

	magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x = vec.x / magnitude;
	vec.y = vec.y / magnitude;
	vec.z = vec.z / magnitude;
	return (vec);
}

/*
** @brief cross product of two vectors
**
** @param a
** @param b
** @return ** cl_float4
*/

cl_float4	cross_product(cl_float4 a, cl_float4 b)
{
	cl_float4	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = -a.x * b.z + a.z * b.x;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

cl_float4	vector_matrix_mul(cl_float4 vector, t_matrix matrix)
{
	return ((cl_float4){{
		matrix.s0 * vector.x + matrix.s1 * vector.y + matrix.s2 * vector.z,
		matrix.s4 * vector.x + matrix.s5 * vector.y + matrix.s6 * vector.z,
		matrix.s8 * vector.x + matrix.s9 * vector.y + matrix.sA * vector.z,
		0.0f
	}});
}

cl_float4	point_matrix_mul(cl_float4 point, t_matrix matrix)
{
	return ((cl_float4){{
		matrix.s0 * point.x + matrix.s1 * point.y + matrix.s2 * point.z
			+ matrix.s3,
		matrix.s4 * point.x + matrix.s5 * point.y + matrix.s6 * point.z
			+ matrix.s7,
		matrix.s8 * point.x + matrix.s9 * point.y + matrix.sA * point.z
			+ matrix.sB,
		0.0f
	}});
}

t_matrix	rotate_about_axis(cl_float4 axis, float angle)
{
	cl_float4	a;
	float		sin_theta;
	float		cos_theta;
	t_matrix	m;

	a = norm4(axis);
	sin_theta = sinf(angle);
	cos_theta = cosf(angle);
	m = IDENTITY_MATRIX;
	m.s0 = a.x * a.x + (1 - a.x * a.x) * cos_theta;
	m.s1 = a.x * a.y * (1 - cos_theta) - a.z * sin_theta;
	m.s2 = a.x * a.z * (1 - cos_theta) + a.y * sin_theta;
	m.s3 = 0;
	m.s4 = a.x * a.y * (1 - cos_theta) + a.z * sin_theta;
	m.s5 = a.y * a.y + (1 - a.y * a.y) * cos_theta;
	m.s6 = a.y * a.z * (1 - cos_theta) - a.x * sin_theta;
	m.s7 = 0;
	m.s8 = a.x * a.z * (1 - cos_theta) - a.y * sin_theta;
	m.s9 = a.y * a.z * (1 - cos_theta) + a.x * sin_theta;
	m.sa = a.z * a.z + (1 - a.z * a.z) * cos_theta;
	m.sb = 0;
	return (m);
}
