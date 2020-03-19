/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/03/19 16:32:23 by dmelessa         ###   ########.fr       */
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

void	init_buffers(t_cl_program *program, t_scene *scene,
	t_sampler *sampler)
{
	int ret;

	printf("!\n");
	program->objects = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY
		| CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * scene->nobjects, scene->objects,
		&ret);
	assert(!ret);
	printf("!!\n");
	program->output_image = clCreateBuffer(program->clp.context,
		CL_MEM_READ_WRITE, sizeof(uint32_t) * program->work_size, NULL, &ret);
	assert(!ret);
	cl_error(program, &program->clp, ret);
	program->triangles = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(t_triangle) * scene->ntriangles,
		scene->triangles, &ret);
	assert(!ret);
	cl_error(program, &program->clp, ret);
	program->lights = clCreateBuffer(program->clp.context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, sizeof(t_light) * scene->nlights, scene->lights,
		&ret);
	assert(!ret);
	printf("!!!	\n");
	program->samples = clCreateBuffer(program->clp.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float2) *
		sampler->info.num_sets *
		sampler->info.num_samples, sampler->sample_set, &ret);
	assert(!ret);
	cl_error(program, &program->clp, ret);
}

void init_options(t_render_options *options)
{
	options->shadows = TRUE;
	options->backgorund_color.value = 0x000000af;
	options->depth = 5;
}

/**
** @brief
** allocate memory for buffers
** compile opencl program
** @param cl_program
** @return ** int
*/
int		init_kernel(t_cl_program *program, t_scene *scene,
					t_render_options *options, t_sampler *sampler)
{
	int		ret = 0;

	printf("Initing kernel...\n");
	printf(" Initing opencl... ");
	init_cl(&program->clp);
	printf("done\n");
	/*init starting render options and generate samples*/
	printf(" Initing options... ");
	init_options(options);
	printf("done\n");
	printf(" generating sampler... ");
	new_sampler(sampler, rand_jitter, 25, 83);
	printf("done\n");
	/*init buffers for kernel*/
	printf("Initing buffers... ");
	init_buffers(program, scene, sampler);
	printf("done\n");
	assert(!ret);
	cl_error(program, &program->clp, ret);
	printf(" Buffer inited\n");
	program->program = create_program(program->clp.context);
	printf(" Program created\n");
	/* build kernel program */
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
		DEFAULT_KERNEL_INCLUDE, NULL, NULL);
	cl_error(program, &program->clp, ret);
	printf(" Program builded\n");
	/* create kernel */
	program->kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
		&ret);
	cl_error(program, &program->clp, ret);
	printf("Kernel inited\n");
	return (0);
}

/**
** @brief
** default initialization
** @param window
** @param cl_program
** @return ** int
*/
int		init_rt(t_rt *rt)
{
	printf("initing\n");
	read_data(&rt->scene);
	init_window(&rt->window);
	rt->program.work_size = DEFAULT_WORK_SIZE;
	rt->program.work_group_size = WORK_GROUP_SIZE;
	init_kernel(&rt->program, &rt->scene, &rt->options, &rt->sampler);
	return 0;
}
