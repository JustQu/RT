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

#ifndef  WORLD_H
# define WORLD_H

# define WORK_GROUP_SIZE 128

# ifndef __OPENCL_C_VERSION__
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif
# endif

# ifdef __OPENCL_C_VERSION__
#define cl_float4 float4
#define cl_float3 float3
#define cl_float float
#define cl_int4 int4
#define cl_int3 int3
#define cl_int int
# endif

typedef struct s_material	t_material;
struct					s_material
{
	cl_int				color;
	cl_float			kd;
	cl_float			ks;
	cl_float			n;
	void				*texture;
};

typedef struct s_obj	t_obj;
struct					s_obj
{
	cl_int				type;
	t_material			material;
	cl_float4			origin;
	cl_float4			direction;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
};

typedef struct s_camera	t_camera;
struct					s_camera
{
	cl_float4			origin;
	cl_float4			direction;
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			near_z;
	cl_float			far_z;
	cl_int				fov;
};

#endif
