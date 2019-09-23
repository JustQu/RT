/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:10:09 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:28:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"

/*
** make given matrix zero.
*/

void	mat3_zero(t_mat3 mat)
{
	mat3_copy(MAT3_ZERO, mat);
}

/*
**copy all members of [mat] to [dest]
*/

void	mat3_copy(t_mat3 mat, t_mat3 dest)
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
** make given matrix identity. It is identical with below,
** but it is more easy to do that with this func especially for members
** e.g. mat3_identity(aStruct->aMatrix);
** @code
** mat3_copy(MAT3_IDENTITY, mat); // C only
** // or
** mat3 mat = MAT3_IDENTITY_INIT;
** @endcode
*/

void	mat3_identity(t_mat3 mat)
{
	mat3_copy(MAT3_IDENTITY, mat);
}

/*
** make given matrix array's each element identity matrix
*/

void	mat3_identity_array(t_mat3 *mat, size_t count)
{
	t_mat3	t;
	size_t	i;

	mat3_identity(t);
	i = 0;
	while (i < count)
	{
		mat3_copy(t, mat[i]);
		i++;
	}
}

/*
** trace of matrix
** sum of the elements on the main diagonal from upper left to the lower right
*/

float	mat3_trace(t_mat3 m)
{
	return (m[0][0] + m[1][1] + m[2][2]);
}
