/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:36:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/10 19:44:38 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 720
# define DEFAULT_FOV 90
# define WORK_GROUP_SIZE 128

# ifndef __OPENCL_C_VERSION__
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif
# endif

# ifdef __OPENCL_C_VERSION__
#  define cl_float4 float4
#  define cl_float3 float3
#  define cl_float float
#  define cl_int4 int4
#  define cl_int3 int3
#  define cl_int int
# endif

typedef struct s_material	t_material;
# ifdef _WIN64
__declspec(align(8))
# endif
struct					s_material //32
{
	cl_int				color;
	cl_float			kd;
	cl_float			ks;
	cl_float			n;
	void				*texture;
};

enum	e_types
{
	cone,
	cylinder,
	paraboloid,
	plane,
	sphere,
	torus,
	triangle
};
typedef enum e_types	t_type;

typedef struct s_box	t_box;
#ifdef _WIN64
__declspec(align(8))
#endif
struct					s_box
{
	cl_float4			min;
	cl_float4			max;
};

typedef struct s_obj	t_obj;
# ifdef _WIN64
__declspec(align(8))
# endif
struct					s_obj		//140
{
	t_type				type;
	t_material			material;
	t_box				bounding_box;
	cl_float4			origin;
	cl_float4			direction;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
	cl_float			maxm;
	cl_float			minm;
};

typedef struct s_triangle	t_triangle;
# ifdef _WIN64
__declspec(align(8))
# endif
struct	s_triangle
{
	cl_float4	vertex1;
	cl_float4	vertex2;
	cl_float4	vertex3;
	cl_float4	vector1;
	cl_float4	vector2;
	cl_float4	normal;
};

/**
** @TODO: make transformation matrix
**
*/
typedef struct s_camera	t_camera;
# ifdef _WIN64
__declspec(align(8))
# endif
struct s_camera
{
	cl_float4			origin;
	cl_float4			direction;
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			near_z;
	cl_float			far_z;
	cl_float			angle;
	cl_int				fov;
};

#endif
