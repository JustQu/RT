/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/10 19:55:21 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <assert.h>
# include <math.h>

# ifdef __unix__
# include "SDL2/SDL.h"
# else
# include "SDL.h"
# endif

# include "libft.h"
# include "world.h"
# include "bool.h"

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "ray_tracer.cl"
# else
#  define DEFAULT_KERNEL_FILE "ray_tracer.cl"
# endif

# define DEFAULT_KERNEL_NAME "main" //NOTE: нельзя сделать кернел с именем 'main'\
											на встроенной видеокарте intel

# define DEFAULT_KERNEL_INCLUDE "-I. -I./include -I./src/cl"
# define DEFAULT_WORK_SIZE DEFAULT_WIDTH * DEFAULT_HEIGHT

# ifdef _WIN64
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# else
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# endif

typedef struct	s_sampler
{
	t_sampler_info	info;
	cl_float2		*sample_set;
}			t_sampler;

/**
** @brief
** информация о opencl
*/
typedef struct			s_clp
{
	cl_platform_id		pl_id;
	cl_device_id		de_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;
}						t_clp;

/**
** @brief
** to manipulate sdl windos
*/
typedef struct			s_window
{
	SDL_Window			*ptr;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	uint32_t			*image; // TODO(dmelessa): change to cl_image later
	int					width;
	int					height;
}						t_window;

/**
** @brief
** all information needed to start our kernel
*/
typedef struct s_cl_program	t_cl_program;
struct					s_cl_program
{
	t_clp				clp;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				output_image;
	cl_mem				objects;
	cl_mem				triangles;
	cl_mem				lights;
	cl_mem				samples;
	size_t				work_size;
	size_t				work_group_size;
};

/**
** @brief
** struct containing information about scene: camera, objects, triangles and light sources
*/
typedef struct s_scene	t_scene;
struct					s_scene
{
	t_obj				*objects;
	t_triangle			*triangles;
	t_light				ambient_light;
	t_light				*lights;
	t_camera			camera;
	int					nobjects;
	int					nlights;
	int					ntriangles;
};

typedef struct	s_rt
{
	t_cl_program		program;
	t_window			window;
	t_scene				scene;
	t_sampler			sampler;
	t_render_options	options;
}				t_rt;

cl_program	create_program(cl_context context);
int			read_data(t_scene *scene);
int			init_window(t_window *window);
int 		init_rt(t_rt *rt);

int			catch_event(t_rt *rt);

void		cl_error(t_cl_program *program, t_clp *clp, int code);

void		new_sampler(t_sampler *sampler, t_sampler_type type, int num_samples, int num_sets);

cl_float2 *generate_samples(t_sampler_info options);

float		rand_float();

#endif
