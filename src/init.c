/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/16 19:07:10 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/**
** @brief
** get
**  opencl GPU device
** create opencl context and command queue
** @param clp
** @return ** int
*/
int		init_cl(t_clp *clp)
{
	if (clp == NULL)
		return (1);
	clp->pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), &(clp->ret_num_platforms));
	assert(!clp->ret);
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_GPU, 1, &(clp->de_id),
						&(clp->ret_num_devices));
	assert(!clp->ret);
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL,
						&(clp->ret));
	assert(!clp->ret);
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	assert(!clp->ret);
	return (0);
}

/**
** @brief
** allocate memory for buffers
** compile opencl program
** @param cl_program
** @return ** int
*/
int		init_renderer(t_cl_program *program, t_scene *scene)
{
	int		ret;

	init_cl(&program->clp);
	program->objects = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * scene->nobjects, scene->objects,
		&ret);
	program->output_image = clCreateBuffer(program->clp.context,
		CL_MEM_READ_WRITE, sizeof(uint32_t) * program->work_size, NULL, &ret);
	cl_error(program, &program->clp, ret);
	program->triangles = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(t_triangle) * scene->ntriangles,
		scene->triangles, &ret);
	cl_error(program, &program->clp, ret);
	program->program = create_program(program->clp.context);
	cl_error(program, &program->clp, ret);
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
							 DEFAULT_KERNEL_INCLUDE, NULL, NULL);
	cl_error(program, &program->clp, ret);
	program->kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
		&ret);
	cl_error(program, &program->clp, ret);
	return (0);
}

/**
** @brief
** default initialization
** @param window
** @param cl_program
** @return ** int
*/
int		init(t_window *window, t_cl_program *cl_program,
						t_scene *scene, char *file)
{
	read_data(scene, file);/*
	init_window(window);
	cl_program->work_size = DEFAULT_WORK_SIZE;
	cl_program->work_group_size = WORK_GROUP_SIZE;
	init_renderer(cl_program, scene);*/
	return 0;
}
