/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:27:56 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:29:09 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "aabb.h"
# endif

typedef struct s_bvh_node	t_bvh_node;

/*
** array of nodes will represent the struct itself
*/

typedef struct s_bvh_node	*t_bvh;

/*
** 48 bytes
** todo: remove center field
*/

struct			s_bvh_node
{
	t_bbox		aabb;
	cl_float3	center;
	int			instance_id;
	int			next;
	int			gap[2];
};

#endif
