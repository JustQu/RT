/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_rt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 00:29:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 19:57:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_RT_H
# define CL_RT_H

#define K_HUGE_VALUE 1e4f
#define EPSILON 1e-4f
#define SAMPLES 1
#define BOUNCES 2

typedef struct s_scene				t_scene;

typedef struct s_sampler_manager	t_sampler_manager;

typedef struct s_ray				t_ray;
typedef struct s_hit_information	t_hit_info;
typedef struct s_shade_rec			t_shade_rec;

typedef float16						t_matrix;

typedef struct				s_kernel_buffer
{
	__global t_ray			*rays;
	__global uchar4			*flags;
}							t_kernel_buffer;

typedef struct				s_texture_manager
{
	__global t_texture		*textures;
	__global float4			*perlin_noise;
	// __global float			*perlin_noise_float;
	__global int			*perm_x;
	__global int			*perm_y;
	__global int			*perm_z;
}							t_texture_manager;

typedef struct				s_instance_manager
{
	__constant t_instance	*instances;
	__global t_obj			*objects;
	__constant t_triangle	*triangles;
	__global t_matrix		*matrices;

	t_texture_manager		tex_mngr;

	int						ninstances;
	int						nobjects;
	int						ntriangles;
	int						nmatrices;
}							t_instance_manager;

struct						s_scene
{
	t_instance_manager		instance_manager;
	__constant t_light		*lights;
	__global t_bvh_node		*bvh;
	int						nlights;
	t_camera				camera;
	t_light					ambient_light;
	t_ambient_occluder		ambient_occluder;
};

struct					s_sampler_manager
{
	t_sampler			*sampler;
	__global t_sampler	*samplers;
	__global float2		*samples;
	__global float2		*disk_samples;
	__global float3		*hemisphere_samples;
};

struct		s_ray
{
	float4	origin;
	float4	direction;
};

struct		s_hit_information
{
	float	t; //ray distance
	float	m;
	float	dv; //dot(ray.direction, object.direction)
	float	xv; //dot(ray.origin - object.origin, object.direction)
};

//TODO(dmelessa): change later
struct			s_shade_rec
{
	t_ray		ray;			//for specular highlights
	t_hit_info	hit_info;
	float4		hit_point;		//world coordinates of hit point
	float4		local_hit_point;//for attaching textures to objects
	float4		normal;			//normal at hit point
								//NOTE: maybe not needed here
								// and we can use local variable
	float4		direction;		//for area lights

	int			id;
};

float4 get_reflected_vector(float4 l, float4 n);


t_instance get_instance(t_instance_manager instance_manager, int id);

inline t_matrix get_instance_matrix(t_instance_manager instance_manager, t_instance instance);

inline t_obj get_object_info(t_instance_manager instance_manager, t_instance instance);

inline t_triangle get_triangle_info(t_instance_manager instance_manager, t_instance instance);

#endif
