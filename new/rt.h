/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/01/28 17:23:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "SDL.h"

typedef int t_bool;
# define TRUE 1
# define FALSE 0

/**
** @brief
** информация о opencl
*/
typedef struct s_clp
{
	cl_platform_id pl_id;
	cl_device_id de_id;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;
	cl_context context;
	cl_command_queue queue;
} t_clp;


struct s_window
{
	SDL_Window *ptr;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t *image; // TODO(dmelessa): change to cl_image later
	int width;
	int height;
};

typedef struct s_window t_window;

struct s_cl_program
{
	cl_program program;
	cl_kernel kernel;
	cl_mem input;
	cl_mem output;
	size_t work_size;
	size_t work_group_size;
	char *source_str;
};

typedef struct s_cl_program t_cl_program;

/**
** @brief
** top level struct of the program
** that info and contains other structs
*/
typedef struct s_program t_program;
struct s_program
{
	t_window window;
	t_clp clp; //opencl common info
	t_cl_program program;
	void *data;
};


typedef struct s_ray t_ray;
struct s_ray
{
	cl_float4 origin;
	cl_float4 direction;
};

typedef struct s_material t_material;
struct s_material
{
	cl_int4 color;
	cl_float kd;
	cl_float ks;
	cl_float n;
	void *texture;
};

typedef struct s_obj t_obj;
struct s_obj
{
	cl_int type;
	t_material material;
	cl_float4 origin;
	cl_float4 direction;
	cl_float r;
	cl_float r2;
	cl_float angle;
	cl_int maxm;
};

typedef struct s_camera t_camera;
struct s_camera
{
	cl_float4 origin;
	cl_float4 direction;
	cl_float ratio;
	cl_float inv_w;
	cl_float inv_h;
	cl_float near_z;
	cl_float far_z;
	cl_int fov;
};

typedef struct s_scene t_scene;
struct s_scene
{
	t_obj objects;
	t_camera camera;
};

#endif
