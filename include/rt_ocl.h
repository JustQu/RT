/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ocl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:45:58 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:09:56 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OCL_H
# define RT_OCL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif
# include "rt_options.h"
# include "scene.h"
# include "sampler_manager.h"
# include "window.h"
# include "image.h"

# define KERNEL_NAME "main_kernel"
# define KERNEL_INC "-I./include -I./srcs/cl"

# ifdef _WIN64
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
#  define DEFAULT_KERNEL_DIR "./srcs/cl/"
# else
#  define DEFAULT_KERNEL_FILE "main_kernel.cl"
#  define DEFAULT_KERNEL_DIR "./srcs/cl/"
# endif

/*
** NOTE: нельзя сделать кернел с именем 'main'
** на встроенной видеокарте intel
*/

# define DEFAULT_KERNEL_NAME	"main_kernel"

# define DEFAULT_KERNEL_INCLUDE	"-I ./include -I ./srcs/cl"
# define DEFAULT_WORK_SIZE		DEFAULT_WIDTH * DEFAULT_HEIGHT
# define WORK_GROUP_SIZE 64

/*
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

/*
** @brief
** all information needed to start our kernel
*/

typedef struct			s_cl_program
{
	t_clp				info;

	cl_program			program;

	cl_kernel			kernel;
	cl_kernel			new_kernel;
	cl_kernel			help_kernel;
	cl_kernel			julia_kernel;

	cl_mem				rgb_image;
	cl_mem				output_image;
	cl_mem				buff;

	cl_mem				instances;
	cl_mem				objects;
	cl_mem				triangles;
	cl_mem				matrices;
	cl_mem				lights;
	cl_mem				bvh;

	cl_mem				textures;
	cl_mem				ranvec;
	cl_mem				perm_x;
	cl_mem				perm_y;
	cl_mem				perm_z;

	cl_mem				samplers;
	cl_mem				samples;
	cl_mem				disk_samples;
	cl_mem				hemisphere_samples;

	size_t				work_size;
	size_t				work_group_size;
}						t_cl_program;

typedef struct s_rt	t_rt;

int						init_ocl(t_cl_program *const program,
								t_window const *const window,
								t_image *const image,
								cl_device_type const device_type);
cl_program				create_program(cl_context context);
void					cleanup_buffers(t_cl_program ocl_program);

#endif
