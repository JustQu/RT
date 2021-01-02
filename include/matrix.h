/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 12:47:05 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:30:25 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef cl_float16				t_matrix;

# define IDENTITY_MATRIX (t_matrix){{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}}
# define ZERO_MATRIX (t_matrix){{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}

/*
** @brief Identity matrix
*/

static const t_matrix g_default_matrix = {
	.s0 = 1.0f, .s1 = 0.0f, .s2 = 0.0f, .s3 = 0.0f,
	.s4 = 0.0f, .s5 = 1.0f, .s6 = 0.0f, .s7 = 0.0f,
	.s8 = 0.0f, .s9 = 0.0f, .sA = 1.0f, .sB = 0.0f,
	.sC = 0.0f, .sD = 0.0f, .sE = 0.0f, .sF = 1.0f
};

void		print_matrix(t_matrix matrix);

t_matrix	mul_matrix(t_matrix a, t_matrix b);

t_matrix	get_x_rotation_matrix(float angle);
t_matrix	get_y_rotation_matrix(float angle);
t_matrix	get_z_rotation_matrix(float angle);
t_matrix	get_inverse_x_rotation_matrix(float angle);
t_matrix	get_inverse_y_rotation_matrix(float angle);
t_matrix	get_inverse_z_rotation_matrix(float angle);

t_matrix	get_scale_matrix(cl_float3 scaling);
t_matrix	get_rotation_matrix(cl_float3 rotation);
t_matrix	get_translation_matrix(cl_float3 translation);

t_matrix	get_inverse_scale_matrix(cl_float3 scaling);
t_matrix	get_inverse_rotation_matrix(cl_float3 rotation);
t_matrix	get_inverse_translation_matrix(cl_float3 translation);

#endif
