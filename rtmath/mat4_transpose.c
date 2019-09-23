/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transpose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:32:29 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:21:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** transpose mat4 and store in dest
** source matrix will not be transposed unless dest is m
** todo: error when dest and m is the same matrix
*/

void	mat4_transpose_to(t_mat4 m, t_mat4 dest)
{
	dest[0][0] = m[0][0];
	dest[0][1] = m[1][0];
	dest[0][2] = m[2][0];
	dest[0][3] = m[3][0];
	dest[1][0] = m[0][1];
	dest[1][1] = m[1][1];
	dest[1][2] = m[2][1];
	dest[1][3] = m[3][1];
	dest[2][0] = m[0][2];
	dest[2][1] = m[1][2];
	dest[2][2] = m[2][2];
	dest[2][3] = m[3][2];
	dest[3][0] = m[0][3];
	dest[3][1] = m[1][3];
	dest[3][2] = m[2][3];
	dest[3][3] = m[3][3];
}

/*
** tranpose mat4 and store result in same matrix
*/

void	mat4_transpose(t_mat4 m)
{
	t_mat4 d;

	mat4_transpose_to(m, d);
	mat4_copy(d, m);
}

/*
** swap two matrix columns
*/

void	mat4_swap_col(t_mat4 mat, int col1, int col2)
{
	t_vec4 tmp;

	vec4_copy(mat[col1], tmp);
	vec4_copy(mat[col2], mat[col1]);
	vec4_copy(tmp, mat[col2]);
}

/*
** swap two matrix rows
*/

void	mat4_swap_row(t_mat4 mat, int row1, int row2)
{
	t_vec4 tmp;

	tmp[0] = mat[0][row1];
	tmp[1] = mat[1][row1];
	tmp[2] = mat[2][row1];
	tmp[3] = mat[3][row1];
	mat[0][row1] = mat[0][row2];
	mat[1][row1] = mat[1][row2];
	mat[2][row1] = mat[2][row2];
	mat[3][row1] = mat[3][row2];
	mat[0][row2] = tmp[0];
	mat[1][row2] = tmp[1];
	mat[2][row2] = tmp[2];
	mat[3][row2] = tmp[3];
}
