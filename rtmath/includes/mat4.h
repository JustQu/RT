/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:25:03 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:36:08 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include "rt_types.h"
# include "vec3.h"
# include "stddef.h"

/*
** for size_t
*/

# include "stdint.h"

# define MAT4_IDENTITY_INIT {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}

# define MAT4_ZERO_INIT {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}

# define MAT4_IDENTITY ((t_mat4)MAT4_IDENTITY_INIT)
# define MAT4_ZERO     ((t_mat4)MAT4_ZERO_INIT)

void	mat4_copy(t_mat4 mat, t_mat4 dest);
void	mat4_identity(t_mat4 mat);
void	mat4_identity_array(t_mat4 *mat, size_t count);
void	mat4_zero(t_mat4 mat);
void	mat4_pick3(t_mat4 mat, t_mat3 dest);
void	mat4_pick3t(t_mat4 mat, t_mat3 dest);
void	mat4_ins3(t_mat3 mat, t_mat4 dest);
void	mat4_mul(t_mat4 m1, t_mat4 m2, t_mat4 dest);

/*
**void	mat4_mulN(t_mat4 *matrices[], uint32_t len, t_mat4 dest);
*/

void	mat4_vec4_mul(t_mat4 m, t_vec4 v, t_vec4 dest);
float	mat4_trace(t_mat4 m);
float	mat4_trace3(t_mat4 m);

/*
**void	mat4_quat(t_mat4 m, t_versor dest);
*/

void	mat4_vec3_mul(t_mat4 m, t_vec3 v, float last, t_vec3 dest);
void	mat4_transpose_to(t_mat4 m, t_mat4 dest);
void	mat4_transpose(t_mat4 m);
void	mat4_scale(t_mat4 m, float s);

/*
**float	mat4_det(t_mat4 mat);
*/

/*
**void	mat4_inv(t_mat4 mat, t_mat4 dest);
*/

void	mat4_swap_col(t_mat4 mat, int col1, int col2);
void	mat4_swap_row(t_mat4 mat, int row1, int row2);
float	mat4_rmc(t_vec4 r, t_mat4 m, t_vec4 c);

#endif
