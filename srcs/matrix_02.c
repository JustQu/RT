/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:22:05 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/17 15:22:06 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

/*
** @brief Get the inverse rotation matrix object
**
** @param v
** @return ** t_matrix
*/

t_matrix	get_inverse_rotation_matrix(cl_float3 v)
{
	t_matrix	matrix;

	matrix = get_inverse_x_rotation_matrix(v.x);
	matrix = mul_matrix(matrix, get_inverse_y_rotation_matrix(v.y));
	matrix = mul_matrix(matrix, get_inverse_z_rotation_matrix(v.z));
	return (matrix);
}

t_matrix	get_translation_matrix(cl_float3 v)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s3 = v.x;
	matrix.s7 = v.y;
	matrix.sB = v.z;
	return (matrix);
}

/*
** @brief Get the inverse translation matrix object
**
** @param v
** @return ** t_matrix
*/

t_matrix	get_inverse_translation_matrix(cl_float3 v)
{
	t_matrix	matrix;

	matrix = g_default_matrix;
	matrix.s3 = -v.x;
	matrix.s7 = -v.y;
	matrix.sB = -v.z;
	return (matrix);
}

t_matrix	get_scale_matrix(cl_float3 v)
{
	return (t_matrix){
			.s0 = v.x, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
			.s4 = 0.0f, .s5 = v.y, .s6 = 0.0f, .s7 = 0.0f,
			.s8 = 0.0f, .s9 = 0.0f, .sA = v.z, .sB = 0.0f,
			.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}

/*
** @brief Get the inverse scale matrix object
**
** @param v
** @return ** t_matrix
*/

t_matrix	get_inverse_scale_matrix(cl_float3 v)
{
	return (t_matrix){
			.s0 = 1.0f / v.x, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
			.s4 = 0.0f, .s5 = 1.0f / v.y, .s6 = 0.0f, .s7 = 0.0f,
			.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f / v.z, .sB = 0.0f,
			.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f};
}
