/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:24:16 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:45:30 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** make given matrix identity. It is identical with below,
**      but it is more easy to do that with this func especially for members
**      e.g. mat4_identity(aStruct->aMatrix);
**
** mat4_copy(MAT4_IDENTITY, mat); // C only
** // or
** mat4 mat = MAT4_IDENTITY_INIT;
*/

void	mat4_identity(t_mat4 mat)
{
	mat4_copy(MAT4_IDENTITY, mat);
}

/*
**make given matrix array's each element identity matrix
*/

void	mat4_identity_array(t_mat4 *mat, size_t count)
{
	t_mat4	t;
	size_t	i;

	mat4_identity(t);
	i = 0;
	while (i < count)
	{
		mat4_copy(t, mat[i]);
		i++;
	}
}

/*
** make given matrix zero.
*/

void	mat4_zero(t_mat4 mat)
{
	mat4_copy(MAT4_ZERO, mat);
}
