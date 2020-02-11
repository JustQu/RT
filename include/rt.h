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

# include "SDL.h"

# include "libft.h"
# include "world.h"

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 640

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "../beautiful_gradient.cl"
# else
#  define DEFAULT_KERNEL_FILE "./beautiful_gradient.cl"
# endif

# define DEFAULT_KERNEL_NAME "render2"

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

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

enum	e_types
{
	sphere,
	plane,
	cone,
	cylinder
};
typedef enum e_types	t_type;

typedef struct s_cl_program	t_cl_program;
struct					s_cl_program
{
	t_clp				clp;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				input;
	cl_mem				output;
	size_t				work_size;
	size_t				work_group_size;
	char				*source_str;
};

typedef struct s_scene	t_scene;
struct					s_scene
{
	t_obj				*objects;
	t_camera			camera;
	int					nobjects;
};

int init(t_window *window, t_cl_program *cl_program, t_scene *scene);

#endif
