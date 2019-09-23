/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:27:31 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:24:04 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** multiply m1 and m2 to dest
**
** m1, m2 and dest matrices can be same matrix, it is possible to write this:
**
** @code
** mat4 m = MAT4_IDENTITY_INIT;
** mat4_mul(m, m, m);
** @endcode
*/

/*
** norm later
*/

/*
**void	mat4_mul(t_mat4 m1, t_mat4 m2, t_mat4 dest)
**{
**	float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
**        a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
**        a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
**        a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3],
**        b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b03 = m2[0][3],
**        b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2], b13 = m2[1][3],
**        b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2], b23 = m2[2][3],
**        b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2], b33 = m2[3][3];
**
**	dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
**	dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
**	dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
**	dest[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
**	dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
**	dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
**	dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
**	dest[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
**	dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
**	dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
**	dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
**	dest[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
**	dest[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
**	dest[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
**	dest[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
**	dest[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
**}
*/

/*
** mupliply N mat4 matrices and store result in dest
**
** this function lets you multiply multiple (more than two or more...) matrices
** multiplication will be done in loop, this may reduce instructions
** size but if len is too small then compiler may unroll whole loop,
** usage:
** @code
** mat m1, m2, m3, m4, res;dest[2][3] = m[3][2];
**
** mat4_mulN((mat4 *[]){&m1, &m2, &m3, &m4}, 4, res);
** @endcode
**
** @warning matrices parameter is pointer array not mat4 array!
*/

/*
**void	mat4_mulN(t_mat4 *matrices[], uint32_t len, t_mat4 dest)
**{
**	uint32_t i;
**
**	mat4_mul(*matrices[0], *matrices[1], dest);
**	for (i = 2; i < len; i++)
**		mat4_mul(dest, *matrices[i], dest);
**}
*/

/*
** multiply mat4 with vec4 (column vector) and store in dest vector
*/

void	mat4_vec4_mul(t_mat4 m, t_vec4 v, t_vec4 dest)
{
	t_vec4	res;

	res[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
	res[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
	res[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
	res[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
	vec4_copy(res, dest);
}

/*
**multiply vector with mat4
**
**m    mat4(affine transform)
**v    vec3
**last 4th item to make it vec4
**dest result vector (t_vec3)
*/

void	mat4_vec3_mul(t_mat4 m, t_vec3 v, float last, t_vec3 dest)
{
	t_vec4	res;

	vec3_to_vec4(v, last, res);
	mat4_vec4_mul(m, res, res);
	vec4_to_vec3(res, dest);
}

/*
** scale (multiply with scalar) matrix without
** multiply matrix with scalar
*/

void	mat4_scale(t_mat4 m, float s)
{
	m[0][0] *= s;
	m[0][1] *= s;
	m[0][2] *= s;
	m[0][3] *= s;
	m[1][0] *= s;
	m[1][1] *= s;
	m[1][2] *= s;
	m[1][3] *= s;
	m[2][0] *= s;
	m[2][1] *= s;
	m[2][2] *= s;
	m[2][3] *= s;
	m[3][0] *= s;
	m[3][1] *= s;
	m[3][2] *= s;
	m[3][3] *= s;
}

/*
** helper for  R (row vector) * M (matrix) * C (column vector)
**
** rmc stands for Row * Matrix * Column
** the result is scalar because R * M = Matrix1x4 (row vector),
** then Matrix1x4 * Vec4 (column vector) = Matrix1x1 (Scalar)
*/

float	mat4_rmc(t_vec4 r, t_mat4 m, t_vec4 c)
{
	t_vec4	tmp;

	mat4_vec4_mul(m, c, tmp);
	return (vec4_dot(r, tmp));
}
