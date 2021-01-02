/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:22:07 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/21 17:32:01 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

/*
** @brief create scale matrix from vector
**
** vector.x		0			0			0
** 0			vector.y	0			0
** 0			0			vector.z	0
** 0			0			0			1
**
** @param scale
** @return ** t_matrix
*/

t_matrix	scale_matrix(cl_float4 scale)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s[0] = scale.s[0];
	matrix.s[5] = scale.s[1];
	matrix.s[10] = scale.s[2];
	return (matrix);
}

/*
** @brief Create translation matrix from vector
**
** 1	0	0	vector.x
** 0	1	0	vector.y
** 0	0	1	vector.z
** 0	0	0	1
**
** @param origin
** @return ** t_matrix
*/

t_matrix	move_matrix(cl_float4 origin)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s[3] = origin.s[0];
	matrix.s[7] = origin.s[1];
	matrix.s[11] = origin.s[2];
	return (matrix);
}

/*
** @brief Get the inverse y rotation matrix object
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_inverse_y_rotation_matrix(float angle)
{
	float	sina;
	float	cosa;

	cosa = cosf(angle * (float)M_PI / 180.0f);
	sina = sinf(angle * (float)M_PI / 180.0f);
	return (t_matrix){
			.s0 = cosa, .s1 = 0.0f, .s2 = -sina, .s3 = 0.0f,
			.s4 = 0.0f, .s5 = 1.0f, .s6 = 0.0f, .s7 = 0.0f,
			.s8 = sina, .s9 = 0.0f, .sA = cosa, .sB = 0.0f,
			.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/*
** @brief Get the inverse z rotation matrix object
**
** @param angle
** @return ** t_matrix
*/

t_matrix	get_inverse_z_rotation_matrix(float angle)
{
	float	sina;
	float	cosa;

	cosa = cosf(angle * (float)M_PI / 180.0f);
	sina = sinf(angle * (float)M_PI / 180.0f);
	return (t_matrix){
			.s0 = cosa, .s1 = sina, .s2 = 0.0f, .s3 = 0.0f,
			.s4 = -sina, .s5 = cosa, .s6 = 0.0f, .s7 = 0.0f,
			.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f, .sB = 0.0f,
			.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/*
** @brief Get the rotation matrix object
** Поскольку мы умножаем на вектор столбец,
** нам надо умножать матрицы в обратном порядке
** @param v rotation vector
** @return ** t_matrix
*/

t_matrix	get_rotation_matrix(cl_float3 v)
{
	t_matrix	matrix;

	matrix = get_z_rotation_matrix(v.z);
	matrix = mul_matrix(matrix, get_y_rotation_matrix(v.y));
	matrix = mul_matrix(matrix, get_x_rotation_matrix(v.x));
	return (matrix);
}
