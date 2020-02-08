/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:56:36 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/28 15:07:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#include <SDL.h>
#else
#include <CL/cl.h>
#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include "libft.h"
# include <math.h>
# include "rtmath.h"
# include <fcntl.h>
# include "defines.h"

# define BUTH SCREEN_HEIGHT / 30
# define BUTW SCREEN_WIDTH / 20

typedef struct	s_windata
{
	SDL_Renderer	*ren;
	SDL_Window		*win;
}				t_windata;

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

typedef union	u_color
{
	unsigned char	bgra[4];
	int				color;
}				t_color;

typedef enum	e_objs
{
	none,
	sphere,
	plane,
	cone,
	cylinder,
	light,
	camera
}				t_obj_type;

typedef enum	e_eqparams
{
	a, b, c, d
}				t_eqparams;

typedef struct	s_material
{
	t_color		diff_color;
	float		kd;
	float		ks;
	float		n;
}				t_material;

typedef struct	s_light_source
{
	t_vec4		origin;
	float		intensity;
	t_vec4		c_s;
}				t_light_source;

typedef struct	s_obj
{
	t_obj_type	type;
	t_vec4		c_s;
	t_vec4		origin;
	t_vec4		hit_point;
	t_vec4		surf_normal;
	t_material	mat;
	float		t;
	void		*data;
}				t_obj;

typedef struct	s_ray
{
	t_vec4		point;
	t_vec4		vec;
}				t_ray;

typedef struct	s_sphere
{
	float		radius;
	float		radius2;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		nv;
}				t_plane;

typedef struct	s_cone
{
	t_vec3		dir;
	float		angle;
	float		k;
	float		k2;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec4		dir;
	float		radius;
}				t_cylinder;

typedef	struct	s_world
{
	t_obj			*objs;
	int				nobjs;
	t_light_source	*lights;
	int				nlights;
}				t_world;

typedef struct	s_camera
{
	t_vec4		origin;
	t_vec4		orient;
	t_mat4		inv_rot;
	int			fov;
	float		near_z;
	float		far_z;
	float		inv_w;
	float		inv_h;
	float		ratio;
	float		angle;
}				t_camera;

typedef struct	s_clp
{
	cl_platform_id		pl_id;
	cl_device_id		de_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;
}				t_clp;

typedef struct	s_param
{
	t_world		world;
	t_camera	camera;
	t_obj		*cntrld_obj;
	t_windata	windata;
	Uint32		*img;
	t_clp		*clprm;
	int			fd;
}				t_param;
// ui

typedef struct	s_rectangle
{
	int	x;
	int	y;
	int	w;
	int	h;
}				t_rectangle;

// типы данных для передачи в видео память

typedef struct	s_spheret
{
	cl_float	radius;
	cl_float	radius2;
}				t_spheret;

typedef struct	s_planet
{
	cl_float4	nv;
}				t_planet;

typedef struct	s_conet
{
	cl_float4	dir;
	cl_float	angle;
	cl_float	k;
	cl_float	k2;
}				t_conet;

typedef struct	s_cylindert
{
	cl_float4	dir;
	cl_float	radius;
}				t_cylindert;

typedef struct	s_materialt
{
	cl_int4		diff_color;
	cl_float	kd;
	cl_float	ks;
	cl_float	n;
}				t_materialt;

typedef struct	s_objt
{
	cl_int		type;
	cl_float4	c_s;
	cl_float4	origin;
	t_materialt	mat;
	cl_float4	dir;
	cl_float	r;
	cl_float	r2;
	cl_float	angle;
}				t_objt ;

typedef struct	s_light_sourcet
{
	cl_float4		origin;
	cl_float		intensity;
	cl_float4		c_s;
}				t_light_sourcet;

typedef	struct	s_worldt
{
	t_objt			*objs;
	cl_int			nobjs;
	t_light_sourcet	*lights;
	cl_int			nlights;
}				t_worldt;

typedef struct	s_camerat
{
	cl_float4	origin;
	cl_float4	orient;
	cl_int		fov;
	cl_float	near_z;
	cl_float	far_z;
	cl_float	inv_w;
	cl_float	inv_h;
	cl_float	ratio;
	cl_float	angle;
}				t_camerat;

void			world_to_camera(t_param *p);

void			set_default_camera(t_camera *camera);
int				read_all(int fd, t_param *p);
void			read_vec3_param(char *str, t_vec3 v3param,
				char *param, t_vec3 v3def);
float			read_fparam(char *str, char *param, float dfval);
void			parse_obj(t_list *l, t_param *p, t_obj_type t);
t_material		read_material(t_color dcolor);

void			delete_lst(void *s, size_t size);

t_obj_type		find_type(t_list *l);
char			*str_to_low(char *str);
void			convert_to16(int val, char *num, char *ax);
char			*ft_itoaf(float val, int fdigits);


size_t read_kernel(char *file_name, char **str);

#endif