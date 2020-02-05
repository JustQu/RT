/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:34:22 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:30:40 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

/*
** convert mat4's rotation part to quaternion
*/

/*
** norm later
*/

/*
**it seems using like m12 instead of m[1][2] causes extra instructions
*/

/*
**void	mat4_quat(t_mat4 m, t_versor dest)
**{
**	float	trace;
**	float	r;
**	float	rinv;
**
**
**
**	trace = m[0][0] + m[1][1] + m[2][2];
**	if (trace >= 0.0f)
**	{
**		r       = sqrtf(1.0f + trace);
**		rinv    = 0.5f / r;
**		dest[0] = rinv * (m[1][2] - m[2][1]);
**		dest[1] = rinv * (m[2][0] - m[0][2]);
**		dest[2] = rinv * (m[0][1] - m[1][0]);
**		dest[3] = r    * 0.5f;
**	}
**	else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
**	{
**    	r       = sqrtf(1.0f - m[1][1] - m[2][2] + m[0][0]);
**    	rinv    = 0.5f / r;
**		dest[0] = r    * 0.5f;
**		dest[1] = rinv * (m[0][1] + m[1][0]);
**		dest[2] = rinv * (m[0][2] + m[2][0]);
**		dest[3] = rinv * (m[1][2] - m[2][1]);
**	}
**	else if (m[1][1] >= m[2][2])
**	{
**	r       = sqrtf(1.0f - m[0][0] - m[2][2] + m[1][1]);
**	rinv    = 0.5f / r;
**	dest[0] = rinv * (m[0][1] + m[1][0]);
**	dest[1] = r    * 0.5f;
**	dest[2] = rinv * (m[1][2] + m[2][1]);
**	dest[3] = rinv * (m[2][0] - m[0][2]);
**	}
**	else
**	{
**    	r       = sqrtf(1.0f - m[0][0] - m[1][1] + m[2][2]);
**    	rinv    = 0.5f / r;
**    	dest[0] = rinv * (m[0][2] + m[2][0]);
**    	dest[1] = rinv * (m[1][2] + m[2][1]);
**    	dest[2] = r    * 0.5f;
**    	dest[3] = rinv * (m[0][1] - m[1][0]);
**	}
**}
*/

/*
** mat4 determinant
*/

/*
** norm later
*/

/*
**float	mat4_det(t_mat4 mat)
**{
**	float t[6];
**	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
**        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
**        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
**        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];
**
**	t[0] = k * p - o * l;
**	t[1] = j * p - n * l;
**	t[2] = j * o - n * k;
**	t[3] = i * p - m * l;
**	t[4] = i * o - m * k;
**	t[5] = i * n - m * j;
**	return (a * (f * t[0] - g * t[1] + h * t[2])
**       - b * (e * t[0] - g * t[3] + h * t[4])
**       + c * (e * t[1] - f * t[3] + h * t[5])
**       - d * (e * t[2] - f * t[4] + g * t[5]));
**}
*/

/*
** inverse mat4 and store in dest
*/

/*
**norm later
*/

/*
**void	mat4_inv(t_mat4 mat, t_mat4 dest)
**{
**	float t[6];
**	float det;
**	float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
**        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
**        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
**        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];
**
**	t[0] = k * p - o * l;
**	t[1] = j * p - n * l;
**	t[2] = j * o - n * k;
**	t[3] = i * p - m * l;
**	t[4] = i * o - m * k;
**	t[5] = i * n - m * j;
**	dest[0][0] =  f * t[0] - g * t[1] + h * t[2];
**	dest[1][0] =-(e * t[0] - g * t[3] + h * t[4]);
**	dest[2][0] =  e * t[1] - f * t[3] + h * t[5];
**	dest[3][0] =-(e * t[2] - f * t[4] + g * t[5]);
**	dest[0][1] =-(b * t[0] - c * t[1] + d * t[2]);
**	dest[1][1] =  a * t[0] - c * t[3] + d * t[4];
**	dest[2][1] =-(a * t[1] - b * t[3] + d * t[5]);
**	dest[3][1] =  a * t[2] - b * t[4] + c * t[5];
**	t[0] = g * p - o * h;
**	t[1] = f * p - n * h;
**	t[2] = f * o - n * g;
**	t[3] = e * p - m * h;
**	t[4] = e * o - m * g;
**	t[5] = e * n - m * f;
**	dest[0][2] =  b * t[0] - c * t[1] + d * t[2];
**	dest[1][2] =-(a * t[0] - c * t[3] + d * t[4]);
**	dest[2][2] =  a * t[1] - b * t[3] + d * t[5];
**	dest[3][2] =-(a * t[2] - b * t[4] + c * t[5]);
**	t[0] = g * l - k * h;
**	t[1] = f * l - j * h;
**	t[2] = f * k - j * g;
**	t[3] = e * l - i * h;
**	t[4] = e * k - i * g;
**	t[5] = e * j - i * f;
**	dest[0][3] =-(b * t[0] - c * t[1] + d * t[2]);
**	dest[1][3] =  a * t[0] - c * t[3] + d * t[4];
**	dest[2][3] =-(a * t[1] - b * t[3] + d * t[5]);
**	dest[3][3] =  a * t[2] - b * t[4] + c * t[5];
**	det = 1.0f / (a * dest[0][0] + b * dest[1][0]
**              + c * dest[2][0] + d * dest[3][0]);
**	mat4_scale(dest, det);
**}
*/
