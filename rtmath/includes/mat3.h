/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 23:16:54 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:37:47 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT3_H
# define MAT3_H

# include "rt_types.h"
# include "stddef.h"

# define MAT3_IDENTITY_INIT  {{1.f, .0f, .0f}, {.0f, 1.f, .0f}, {.0f, .0f, 1.f}}
# define MAT3_ZERO_INIT      {{.0f, .0f, .0f}, {.0f, .0f, .0f}, {.0f, .0f, .0f}}
# define MAT3_IDENTITY 		((t_mat3)MAT3_IDENTITY_INIT)
# define MAT3_ZERO     		((t_mat3)MAT3_ZERO_INIT)

/*
**copy all members of [mat] to [dest]
*/
void	mat3_copy(t_mat3 mat, t_mat3 dest);

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
void	mat3_identity(t_mat3 mat);

/*
** make given matrix array's each element identity matrix
*/
void	mat3_identity_array(t_mat3 *mat, size_t count);

/*
** make given matrix zero.
*/
void	mat3_zero(t_mat3 mat);

/*
**multiply m1 and m2 to dest
**
** m1, m2 and dest matrices can be same matrix, it is possible to write this:
**
** @code
** mat3 m = MAT3_IDENTITY_INIT;
** mat3_mul(m, m, m);
*/
void	mat3_mul(t_mat3 m1, t_mat3 m2, t_mat3 dest);

/*
**transpose mat3 and store in dest
**
** source matrix will not be transposed unless dest is m
*/
void	mat3_transpose_to(t_mat3 m, t_mat3 dest);

/*
**tranpose mat3 and store result in same matrix
*/
void	mat3_transpose(t_mat3 m);

/*
** multiply mat3 with vec3 (column vector) and store in dest vector
*/
void	mat3_mulv(t_mat3 m, t_vec3 v, t_vec3 dest);

/*
** trace of matrix
** sum of the elements on the main diagonal from upper left to the lower right
*/
float	mat3_trace(t_mat3 m);

/*
** convert mat3 to quaternion
**
** it seems using like m12 instead of m[1][2] causes extra instructions
*/
void	mat3_quat(t_mat3 m, t_versor dest);

/*
** scale (multiply with scalar) matrix
** multiply matrix with scalar
*/
void	mat3_scale(t_mat3 m, float s);

/*
** mat3 determinant
*/
float	mat3_det(t_mat3 mat);

/*
** inverse mat3 and store in dest
*/
void	mat3_inv(t_mat3 mat, t_mat3 dest);

/*
** swap two matrix columns
*/
void	mat3_swap_col(t_mat3 mat, int col1, int col2);

/*
** swap two matrix rows
*/
void	mat3_swap_row(t_mat3 mat, int row1, int row2);

/*
** helper for  R (row vector) * M (matrix) * C (column vector)
** rmc stands for Row * Matrix * Column
** the result is scalar because R * M = Matrix1x3 (row vector),
** then Matrix1x3 * Vec3 (column vector) = Matrix1x1 (Scalar)
*/
float	mat3_rmc(t_vec3 r, t_mat3 m, t_vec3 c);

#endif
