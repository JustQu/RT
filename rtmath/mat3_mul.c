/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:13:15 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:25:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"
#include "vec3.h"

/*
**multiply m1 and m2 to dest
**
** m1, m2 and dest matrices can be same matrix, it is possible to write this:
**
** @code
** mat3 m = MAT3_IDENTITY_INIT;
** mat3_mul(m, m, m);
*/

void	mat3_mul(t_mat3 m1, t_mat3 m2, t_mat3 dest)
{
	t_mat3	tmp;

	tmp[0][0] =
		m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
	tmp[0][1] =
		m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
	tmp[0][2] =
		m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];
	tmp[1][0] =
		m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
	tmp[1][1] =
		m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
	tmp[1][2] =
		m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];
	tmp[2][0] =
		m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
	tmp[2][1] =
		m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
	tmp[2][2] =
		m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
	mat3_copy(tmp, dest);
}

/*
** multiply mat3 with vec3 (column vector) and store in dest vector
*/

void	mat3_mulv(t_mat3 m, t_vec3 v, t_vec3 dest)
{
	dest[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
	dest[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
	dest[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];
}

/*
** scale (multiply with scalar) matrix
** multiply matrix with scalar
*/

void	mat3_scale(t_mat3 m, float s)
{
	m[0][0] *= s;
	m[0][1] *= s;
	m[0][2] *= s;
	m[1][0] *= s;
	m[1][1] *= s;
	m[1][2] *= s;
	m[2][0] *= s;
	m[2][1] *= s;
	m[2][2] *= s;
}

/*
** helper for  R (row vector) * M (matrix) * C (column vector)
** rmc stands for Row * Matrix * Column
** the result is scalar because R * M = Matrix1x3 (row vector),
** then Matrix1x3 * Vec3 (column vector) = Matrix1x1 (Scalar)
*/

float	mat3_rmc(t_vec3 r, t_mat3 m, t_vec3 c)
{
	t_vec3	tmp;

	mat3_mulv(m, c, tmp);
	return (vec3_dot(r, tmp));
}
