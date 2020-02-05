/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_inv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:18:37 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:28:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"
#include "math.h"

/*
** mat3 determinant
*/

float	mat3_det(t_mat3 mat)
{
	return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
		- mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2])
		+ mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]));
}

/*
** inverse mat3 and store in dest
*/

void	mat3_inv(t_mat3 mat, t_mat3 dest)
{
	float	det;
	t_mat3	dest1;

	dest1[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
	dest1[0][1] = -(mat[0][1] * mat[2][2] - mat[2][1] * mat[0][2]);
	dest1[0][2] = mat[0][1] * mat[1][2] - mat[1][1] * mat[0][2];
	dest1[1][0] = -(mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
	dest1[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
	dest1[1][2] = -(mat[0][0] * mat[1][2] - mat[1][0] * mat[0][2]);
	dest1[2][0] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
	dest1[2][1] = -(mat[0][0] * mat[2][1] - mat[2][0] * mat[0][1]);
	dest1[2][2] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	det = 1.0f / (mat[0][0] * dest1[0][0] + mat[0][1] * dest1[1][0]
											+ mat[0][2] * dest1[2][0]);
	mat3_copy(dest1, dest);
	mat3_scale(dest, det);
}

/*
** convert mat3 to quaternion
**
** it seems using like m12 instead of m[1][2] causes extra instructions
*/

/*
**norm later
*/

/*
**void	mat3_quat(t_mat3 m, t_versor dest)
**{
**  float trace;
**  float	r;
**  float	rinv;
**
**  trace = m[0][0] + m[1][1] + m[2][2];
**  if (trace >= 0.0f)
**  {
**    r       = sqrtf(1.0f + trace);
**    rinv    = 0.5f / r;
**    dest[0] = rinv * (m[1][2] - m[2][1]);
**    dest[1] = rinv * (m[2][0] - m[0][2]);
**    dest[2] = rinv * (m[0][1] - m[1][0]);
**    dest[3] = r    * 0.5f;
**  }
**  else if (m[0][0] >= m[1][1] && m[0][0] >= m[2][2])
**  {
**    r       = sqrtf(1.0f - m[1][1] - m[2][2] + m[0][0]);
**    rinv    = 0.5f / r;
**    dest[0] = r    * 0.5f;
**    dest[1] = rinv * (m[0][1] + m[1][0]);
**    dest[2] = rinv * (m[0][2] + m[2][0]);
**    dest[3] = rinv * (m[1][2] - m[2][1]);
**  }
**  else if (m[1][1] >= m[2][2])
**  {
**    r       = sqrtf(1.0f - m[0][0] - m[2][2] + m[1][1]);
**    rinv    = 0.5f / r;
**    dest[0] = rinv * (m[0][1] + m[1][0]);
**    dest[1] = r    * 0.5f;
**    dest[2] = rinv * (m[1][2] + m[2][1]);
**    dest[3] = rinv * (m[2][0] - m[0][2]);
**  }
**  else
**  {
**    r       = sqrtf(1.0f - m[0][0] - m[1][1] + m[2][2]);
**    rinv    = 0.5f / r;
**    dest[0] = rinv * (m[0][2] + m[2][0]);
**    dest[1] = rinv * (m[1][2] + m[2][1]);
**    dest[2] = r    * 0.5f;
**    dest[3] = rinv * (m[0][1] - m[1][0]);
**  }
**}
*/
