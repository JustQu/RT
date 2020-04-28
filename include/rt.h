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
# include <math.h>

# ifdef __unix__
# include "SDL2/SDL.h"
# else
# include "SDL.h"
# include "assert.h"
# endif

# include "libft.h"
# include "world.h"
# include "bool.h"
# include "sampler_manager.h"

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
# else
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
# endif

# define DEFAULT_KERNEL_NAME "main" //NOTE: нельзя сделать кернел с именем 'main'\
											на встроенной видеокарте intel

# define DEFAULT_KERNEL_INCLUDE "-I ./include -I ./src/cl"
# define DEFAULT_WORK_SIZE DEFAULT_WIDTH * DEFAULT_HEIGHT

# ifdef _WIN64
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# else
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# endif

#define SUCCESS 0
#define ERROR -1

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
	cl_mem				samplers;
	cl_mem				samples;
	cl_mem				disk_samples;
	cl_mem				hemisphere_samples;
	size_t				work_size;
	size_t				work_group_size;
};

/** names of types -> read_data() -> init_func() */
#define NUM_OF_TYPES 6
#define TRIANGLE "triangle"

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
	char				*obj_name[NUM_OF_TYPES]; //????
};

typedef struct	s_rt
{
	t_cl_program		program;
	t_window			window;
	t_scene				scene;
	t_sampler_manager	sampler_manager;
	t_render_options	options;
}				t_rt;

/**			functions for scene initialization			*/
cl_float4	get_vector(int *f, int *l, char *line);
float		get_number(int *f, int *l, char *line);
int			find_parentheses(char *line, char *param, int *f, int *l);
void		init_camera(char *line, t_scene *scene);
void		init_object(char *line, t_scene *scene, int type);
void		init_triangle(char *line, t_scene *scene);
char		*find_file_name(char *str);
int			fd_return(char *file_name);
void		read_file(t_scene *scene, char *scene_file);

/* program initialization */
int			init_window(t_window *window);
int			init_rt(t_rt *rt, const char *scene_file);
int			init_sampler_manager(t_sampler_manager *sampler_manager);
cl_program	create_program(cl_context context);

void		read_data(t_scene *scene, t_sampler_manager *sampler_manager, char *scene_file);

	/* events */
int			catch_event(t_rt *rt);

/* errors */
void		cl_error(t_cl_program *program, t_clp *clp, int code);
void		ft_clerror(cl_int ret);

	/* utils */
float		rand_float();
int			rand_int();
void		swap_int(int *a, int *b);
void		swap_float2(cl_float2 *a, cl_float2 *b);

#endif
