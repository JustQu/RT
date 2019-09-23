/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_transpose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:16:25 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:26:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"
#include "vec3.h"

/*
**transpose mat3 and store in dest
**
** source matrix will not be transposed unless dest is m
*/

void	mat3_transpose_to(t_mat3 m, t_mat3 dest)
{
	dest[0][0] = m[0][0];
	dest[0][1] = m[1][0];
	dest[0][2] = m[2][0];
	dest[1][0] = m[0][1];
	dest[1][1] = m[1][1];
	dest[1][2] = m[2][1];
	dest[2][0] = m[0][2];
	dest[2][1] = m[1][2];
	dest[2][2] = m[2][2];
}

/*
**tranpose mat3 and store result in same matrix
*/

void	mat3_transpose(t_mat3 m)
{
	t_mat3 tmp;

	tmp[0][1] = m[1][0];
	tmp[0][2] = m[2][0];
	tmp[1][0] = m[0][1];
	tmp[1][2] = m[2][1];
	tmp[2][0] = m[0][2];
	tmp[2][1] = m[1][2];
	m[0][1] = tmp[0][1];
	m[0][2] = tmp[0][2];
	m[1][0] = tmp[1][0];
	m[1][2] = tmp[1][2];
	m[2][0] = tmp[2][0];
	m[2][1] = tmp[2][1];
}

/*
** swap two matrix columns
*/

void	mat3_swap_col(t_mat3 mat, int col1, int col2)
{
	t_vec3 tmp;

	vec3_copy(mat[col1], tmp);
	vec3_copy(mat[col2], mat[col1]);
	vec3_copy(tmp, mat[col2]);
}

/*
** swap two matrix rows
*/

void	mat3_swap_row(t_mat3 mat, int row1, int row2)
{
	t_vec3 tmp;

	tmp[0] = mat[0][row1];
	tmp[1] = mat[1][row1];
	tmp[2] = mat[2][row1];
	mat[0][row1] = mat[0][row2];
	mat[1][row1] = mat[1][row2];
	mat[2][row1] = mat[2][row2];
	mat[0][row2] = tmp[0];
	mat[1][row2] = tmp[1];
	mat[2][row2] = tmp[2];
}
