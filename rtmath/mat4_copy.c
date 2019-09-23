/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:26:19 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:23:49 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** copy all members of [mat] to [dest]
*/

void	mat4_copy(t_mat4 mat, t_mat4 dest)
{
	dest[0][0] = mat[0][0];
	dest[1][0] = mat[1][0];
	dest[0][1] = mat[0][1];
	dest[1][1] = mat[1][1];
	dest[0][2] = mat[0][2];
	dest[1][2] = mat[1][2];
	dest[0][3] = mat[0][3];
	dest[1][3] = mat[1][3];
	dest[2][0] = mat[2][0];
	dest[3][0] = mat[3][0];
	dest[2][1] = mat[2][1];
	dest[3][1] = mat[3][1];
	dest[2][2] = mat[2][2];
	dest[3][2] = mat[3][2];
	dest[2][3] = mat[2][3];
	dest[3][3] = mat[3][3];
}

/*
**copy upper-left of mat4 to mat3
*/

void	mat4_pick3(t_mat4 mat, t_mat3 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[0][1];
	dest[0][2] = mat[0][2];
	dest[1][0] = mat[1][0];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[1][2];
	dest[2][0] = mat[2][0];
	dest[2][1] = mat[2][1];
	dest[2][2] = mat[2][2];
}

/*
** copy upper-left of mat4 to mat3 (transposed)
** the postfix t stands for transpose
*/

void	mat4_pick3t(t_mat4 mat, t_mat3 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[1][0];
	dest[0][2] = mat[2][0];
	dest[1][0] = mat[0][1];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[2][1];
	dest[2][0] = mat[0][2];
	dest[2][1] = mat[1][2];
	dest[2][2] = mat[2][2];
}

/*
** copy mat3 to mat4's upper-left
*/

void	mat4_ins3(t_mat3 mat, t_mat4 dest)
{
	dest[0][0] = mat[0][0];
	dest[0][1] = mat[0][1];
	dest[0][2] = mat[0][2];
	dest[1][0] = mat[1][0];
	dest[1][1] = mat[1][1];
	dest[1][2] = mat[1][2];
	dest[2][0] = mat[2][0];
	dest[2][1] = mat[2][1];
	dest[2][2] = mat[2][2];
}
