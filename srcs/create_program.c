/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:19:38 by marvin            #+#    #+#             */
/*   Updated: 2020/12/29 15:31:25 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_ocl.h"
#include "rt_error.h"

#include <fcntl.h>

#define BUFF 100000

static const char	*g_files[] = {
	"cl_types.clh",
	"color.h",
	"aabb.h",
	"camera.h",
	"texture.h",
	"material.h",
	"objects.h",
	"light.h",
	"sampler.h",
	"instance.h",
	"bvh.h",
	"rt_options.h",
	"cl_rt.clh",
	"utils.cl",
	"print.cl",
	"solver.cl",
	"random.cl",
	"color.cl",
	"sampler.cl",
	"sampler_manager.cl",
	"matrix.cl",
	"normal.cl",
	"intersection.cl",
	"light.cl",
	"brdf.cl",
	"ambient_occlusion.cl",
	"perlin.cl",
	"material.cl",
	"shade.cl",
	"area_light_shade.cl",
	"ray_tracer.cl",
	"path_tracer.cl",
	"trace.cl",
	"area_light_tracer.cl",
	"camera.cl",
	"main_kernel.cl",
	"util_kernels.cl",
};

static int		g_num_files = sizeof(g_files) / sizeof(char *);

static void		read_file(const char *file_name, char *str)
{
	char	full_file_name[128];
	int		ret;
	int		fd;

	ft_strcpy(full_file_name, DEFAULT_KERNEL_DIR);
	ft_strcpy(full_file_name + sizeof(DEFAULT_KERNEL_DIR) - 1, file_name);
	fd = open(full_file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_strcpy(full_file_name, "./include/");
		ft_strcpy(full_file_name + sizeof("./include/") - 1, file_name);
		fd = open(full_file_name, O_RDONLY);
	}
	rt_is_dead(app_err, system_open_file_error, fd == -1, "create_program 1");
	ret = read(fd, str, BUFF);
	if (ret < 0)
		rt_warning("Warning: Could not read file");
	else
		str[ret] = '\0';
	if (close(fd) == -1)
		rt_warning("Warning: could not close file");
}

cl_program		create_program(cl_context context)
{
	int			ret;
	int			i;
	char		**str;
	cl_program	program;

	i = 0;
	str = ft_memalloc(sizeof(char *) * g_num_files);
	rt_is_dead(system_err, system_malloc_error, !str, "create_program 2");
	ret = 0;
	while (i < g_num_files)
	{
		str[i] = ft_memalloc(sizeof(char) * BUFF);
		rt_is_dead(system_err, system_malloc_error, !str, "create_program 3");
		read_file(g_files[i], str[i]);
		i++;
	}
	program = clCreateProgramWithSource(context,
		g_num_files, (const char **)str, NULL, &ret);
	rt_is_dead(opencl_err, cl_create_program_error, ret, "creat_program 4");
	while (i--)
		ft_strdel(&str[i]);
	ft_memdel((void **)&str);
	return (program);
}
