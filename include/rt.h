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

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "ray_tracer.cl"
# else
#  define DEFAULT_KERNEL_FILE "ray_tracer.cl"
# endif

# define DEFAULT_KERNEL_NAME "raytrace"

# define DEFAULT_KERNEL_INCLUDE "-I ./include -I ./src/cl"
# define DEFAULT_WORK_SIZE DEFAULT_WIDTH * DEFAULT_HEIGHT
# define DEFAULT_WIDTH 1200
# define DEFAULT_HEIGHT 720

# ifdef _WIN64
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# else
#	define DEFAULT_KERNEL_DIR "./src/cl/"
# endif


typedef int	t_bool;
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

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

typedef struct			s_window
{
	SDL_Window			*ptr;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	uint32_t			*image; // TODO(dmelessa): change to cl_image later
	int					width;
	int					height;
}						t_window;

typedef struct s_cl_program	t_cl_program;
struct					s_cl_program
{
	t_clp				clp;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				objects;
	cl_mem				output_image;
	cl_mem				triangles;
	size_t				work_size;
	size_t				work_group_size;
};

#define NUM_OF_TYPES 5
#define TRIANGLE "triangle"

typedef struct s_scene	t_scene;
struct					s_scene
{
	t_obj				*objects;
	t_triangle			*triangles;
	t_box				*boxes; //for test
	t_camera			camera;
	int					nobjects;
	char				*obj_name[NUM_OF_TYPES];
	int					ntriangles;
};

/**			functions for scene initialization			*/
void		init_camera(char *line, t_scene *scene);
void		init_object(char *line, t_scene *scene, int type);
void		init_triangle(char *line, t_scene *scene);
char		*find_file_name(char *str);
int			fd_return(char *file_name);
void		read_data(t_scene *scene, char *name);

cl_program	create_program(cl_context context);
int			init_window(t_window *window);
int 		init(t_window *window, t_cl_program
				*cl_program, t_scene *scene, char *file);

int			catch_event();
void		cl_error(t_cl_program *program, t_clp *clp, int code);

#endif
