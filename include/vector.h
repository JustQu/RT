/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:15:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/19 21:10:34 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "rt_types.h"
# include "matrix.h"

cl_float4	norm4(cl_float4 vec);
cl_float4	cross_product(cl_float4 a, cl_float4 b);
cl_float4	vector_matrix_mul(cl_float4 vector, t_matrix matrix);
cl_float4	point_matrix_mul(cl_float4 point, t_matrix matrix);
t_matrix	rotate_about_axis(cl_float4 axis, float angle);

#endif
