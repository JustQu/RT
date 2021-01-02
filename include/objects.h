/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 11:54:16 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "material.h"
#  include "aabb.h"
# endif

typedef enum e_types		t_type;
typedef struct s_obj		t_obj;
typedef struct s_triangle	t_triangle;
enum	e_types
{
	obj_none = -2,
	cone = 0,
	cylinder,
	paraboloid,
	plane,
	sphere,
	torus,
	triangle,
	box,
	disk,
	rectangle,
	generic_shere,
};

/*
** @brief geometric properties of object
*/
struct					s_obj
{
	cl_float4			origin;
	cl_float4			direction;
	cl_float4			dir2;
	cl_float4			normal;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
	cl_float			maxm;
	cl_float			minm;
	cl_int				shadows;
	cl_int				sampler_id;
	cl_int				boolean;
};

/*
** vector1 = vertex2 - vertex1
** vector2 = vertex3 - vertex1
*/

struct					s_triangle
{
	cl_float4			vertex1;
	cl_float4			vertex2;
	cl_float4			vertex3;
	cl_float4			vector1;
	cl_float4			vector2;
	cl_float4			normal;
};

/*
** auxiliary struct for data transfer between function
** origin also vertex for triangle
*/
typedef struct			s_object_info
{
	t_material			material;
	cl_float4			origin;
	cl_float4			vector1;
	cl_float4			vector2;
	cl_float4			direction;
	cl_float3			rotation;
	cl_float3			scaling;
	t_bbox				bounding_box;
	cl_float			minm;
	cl_float			maxm;
	cl_float			r;
	cl_float			r2;
	t_type				type;
	cl_int				transformed;
}						t_object_info;

#endif
