/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_trace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:38:16 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:24:12 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** trace of matrix
** sum of the elements on the main diagonal from upper left to the lower right
*/

float	mat4_trace(t_mat4 m)
{
	return (m[0][0] + m[1][1] + m[2][2] + m[3][3]);
}

/*
** trace of matrix (rotation part)
** sum of the elements on the main diagonal from upper left to the lower right
*/

float	mat4_trace3(t_mat4 m)
{
	return (m[0][0] + m[1][1] + m[2][2]);
}
