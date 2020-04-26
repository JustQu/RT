/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:36:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/04/26 00:01:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# define DEFAULT_WIDTH 1280
# define DEFAULT_HEIGHT 800
# define DEFAULT_FOV 90
# define WORK_GROUP_SIZE 128

//# define BOUNCES 5
//# define SAMPLES 100
// # define EPSILON  0.00003f /* required to compensate for limited float precision */
// # define PI  3.14159265359f //We dont need this constant since we can use constant from math.h

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
#  define cl_char char
#  define cl_uchar uchar
#  define cl_bool bool
# endif

typedef union s_color			t_color;

typedef enum e_sampler_type		t_sampler_type;
typedef struct s_sampler		t_sampler;

typedef struct s_render_options	t_render_options;

typedef enum e_material_type	t_material_type;
typedef struct s_material		t_material;

typedef enum e_types			t_type;
typedef enum e_light_types		t_light_type;
typedef struct s_obj			t_obj;
typedef struct s_light			t_light;
typedef struct s_triangle		t_triangle;
typedef struct s_bbox			t_bbox;

typedef enum e_camera_type		t_camera_type;
typedef struct s_camera			t_camera;
typedef struct s_viewplane		t_viewplane;

union s_color {
	cl_int value;
	struct
	{
		cl_uchar b;
		cl_uchar g;
		cl_uchar r;
		cl_uchar a;
	};
};

enum	e_sampler_type
{
		none, //maybe we can replace it with regular grid where is onlu one sample per pixel
		regular_grid,
		jitter,
		rand_jitter,
		pure_random,
		nrooks
};

/*
** Sample types flags
*/

#define DEFAULT_SAMPLES		1 << 0
#define DISK_SAMPLES		1 << 1
#define HEMISPHERE_SAMPLES	1 << 2

# ifdef _WIN64
__declspec(align(8))
# endif
struct				s_sampler
{
	t_sampler_type	type;
	cl_int			num_samples; /* the number of sample points in a pattern */
	cl_int			num_sets;	/* the number of sample sets(patterns) stores */
	cl_int			count;		/* the currenct numer of sample points used */
	cl_int			jump;		// random index jump
	cl_int			samples_type; // default / disk / hemisphere

	// cl_int			shuffled_indices[NUM_SAMPLES * NUM_SETS];

	cl_int			offset;
	cl_int			disk_samples_offset;
	cl_int			hemisphere_samples_offset;
};

# ifdef _WIN64
__declspec(align(8))
# endif
struct s_render_options
{
	cl_int			depth;
	cl_int			shadows;
	t_color			backgorund_color;
	cl_int			sampler_id;
};

enum e_material_type
{
	matte, //kd, ka
	phong
};

# ifdef _WIN64
__declspec(align(8))
# endif
struct					s_material //kd + ks < 1.0
{
	t_material_type		type;
	t_color				color;
	cl_float			kd; //diffuse reflection coefficient [0, 1]
	cl_float			ka;
	cl_float			ks; //coefficient of specularreflection [0, 1]
	cl_float			exp;
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

//NOTE: some types will be removed from that list
enum	e_light_types
{
	ambient,
	ambient_occluder,
	directional,
	point,
	area,
	enviromental
};

# ifdef _WIN64
__declspec(align(8))
# endif
struct	s_light
{
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls; //radiance scaling factor [0, inf)
	t_light_type	type;
};

/**
** @brief
** axis-aligned bounding box for object
*/
#ifdef _WIN64
__declspec(align(8))
#endif
struct					s_bbox
{
	cl_float4			min;
	cl_float4			max;
};

# ifdef _WIN64
__declspec(align(8))
# endif
struct					s_obj
{
	t_type				type;
	t_material			material;
	t_bbox				bounding_box;
	cl_float4			origin;
	cl_float4			direction;
	cl_float			r;
	cl_float			r2;
	cl_float			angle;
	cl_float			maxm;
	cl_float			minm;
	cl_bool				shadows;
};

# ifdef _WIN64
__declspec(align(8))
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

enum	e_camera_type
{
		orthographic,
		perspective,
		thin_lens,
		fisheye,
		spherical,
		stereo
};

# ifdef _WIN64
__declspec(align(8))
# endif
struct	s_viewplane
{
	cl_float	pixel_size;
	cl_int		width;
	cl_int		height;
};

/**
** @TODO: make transformation matrix
** TODO: singularity ยง9.9
*/
# ifdef _WIN64
__declspec(align(8))
# endif
struct s_camera
{
	t_viewplane			viewplane;
	cl_float4			origin; // eye
	cl_float4			direction; // lookat - eye
	cl_float4			up; // (0, 1, 0)
	cl_float4			u;
	cl_float4			v; // actually we need only  th3 vectors. the up vector could be hardcodeded and w = -derction
	cl_float4			w;
	cl_float			d; //the view-plane distance
	cl_float			zoom; //zoom factor
	cl_float			exposure_time; //using somewhere later
	t_camera_type		type;
	cl_int				sampler_id; //thin_camera

	//thin-lens camera
	cl_float			lens_radius; //lens radius
	cl_float			f; //focal plane distance

//note: prob not needed
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			angle;
	cl_int				fov;
};

#endif
