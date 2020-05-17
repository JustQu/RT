/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/17 22:19:57 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "types.h"
#include "material.h"

typedef enum e_types				t_type;
typedef struct s_obj				t_obj;
typedef struct s_triangle			t_triangle;
typedef struct s_bbox				t_bbox;
enum	e_types
{
	cone,
	cylinder,
	paraboloid,
	plane,
	sphere,
	torus,
	triangle,
	box,
	disk
};

/**
** @brief
** axis-aligned bounding box for object
*/
#ifdef _WIN64
__declspec(align(4))
#endif
struct					s_bbox
{
	cl_float4			min;
	cl_float4			max;
};

# ifdef _WIN64
__declspec(align(4))
# endif
struct					s_obj
{
	t_type				type;
	t_material			material;
	t_bbox				bounding_box;
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
};

// int a = sizeof(struct s_obj);

# ifdef _WIN64
__declspec(align(4))
# endif
struct	s_triangle
{
	t_material	material;
	cl_float4	vertex1;
	cl_float4	vertex2;
	cl_float4	vertex3;
	cl_float4	vector1; //vertex2 - vertex1
	cl_float4	vector2; // vertex3 - vertex1
	cl_float4	normal;
};

#endif
