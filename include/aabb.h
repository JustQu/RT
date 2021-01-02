/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 23:23:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/04 00:15:18 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

/*
** @brief Axis-aligned bounding box
*/

typedef struct s_aabb	t_aabb;
typedef struct s_aabb	t_bbox;

struct					s_aabb
{
	cl_float4			max;
	cl_float4			min;
};

#endif
