/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/04/25 00:29:49 by dmelessa         ###   ########.fr       */
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
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), NULL);
	ft_clerror(clp->ret);
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_ALL, 1, &(clp->de_id),
							  &(clp->ret_num_devices));
	printf("%d\n", clp->ret);
	assert(!clp->ret);
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL,
		&(clp->ret));
	assert(!clp->ret);
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	ft_clerror(clp->ret);
	return (0);
}

//NOTE: deal with case when there is no objects
//TODO: mem manager like sampler_manager but for scene
void	init_buffers(t_cl_program *program, t_scene *scene,
	t_sampler_manager *sampler_manager)
{
	int			ret;
	int			ro;
	cl_context	cntx;

	ro = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
	cntx = program->clp.context;
	program->output_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
		sizeof(uint32_t) * program->work_size, NULL, &ret);
	cl_error(program, &program->clp, ret);

	program->objects = clCreateBuffer(cntx, ro,
		sizeof(t_obj) * scene->nobjects, scene->objects, &ret);
	cl_error(program, &program->clp, ret);

	program->triangles = clCreateBuffer(cntx, ro,
		sizeof(t_triangle) * scene->ntriangles, scene->triangles, &ret);
	cl_error(program, &program->clp, ret);

	program->lights = clCreateBuffer(cntx, ro, sizeof(t_light) *
		scene->nlights, scene->lights, &ret);
	cl_error(program, &program->clp, ret);

	program->samplers = clCreateBuffer(cntx, ro, sizeof(t_sampler) *
		sampler_manager->count, sampler_manager->samplers, &ret);
	cl_error(program, &program->clp, ret);

	program->samples = clCreateBuffer(cntx, ro, sizeof(cl_float2) *
		sampler_manager->samples_size, sampler_manager->samples, &ret);
	cl_error(program, &program->clp, ret);

	program->disk_samples = clCreateBuffer(cntx, ro, sizeof(cl_float2) *
		sampler_manager->samples_size, sampler_manager->disk_samples, &ret);
	cl_error(program, &program->clp, ret);

	program->hemisphere_samples = clCreateBuffer(cntx, ro, sizeof(cl_float3) *
		sampler_manager->samples_size, sampler_manager->hemisphere_samples, &ret);
	// program->samples = clCreateBuffer(program->clp.context,
	// 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float2) *
	// 	sampler->info.num_sets * sampler->info.num_samples,
	// 	sampler->samples, &ret);
	// program->disk_samples = clCreateBuffer(program->clp.context,
	// 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float2) *
	// 	sampler->info.num_samples * sampler->info.num_sets,
	// 	sampler->disk_samples, &ret);
	// program->hemisphere_samples = clCreateBuffer(program->clp.context,
	// 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_float3) *
	// 	sampler->info.num_samples * sampler->info.num_sets,
	// 	sampler->hemisphere_samples, &ret);
	cl_error(program, &program->clp, ret);
}

void init_options(t_render_options *options, t_sampler_manager *sampler_manager)
{
	options->shadows = TRUE;
	options->backgorund_color.value = 0x000000af;
	options->depth = 5;
	options->sampler_id = new_sampler(sampler_manager, nrooks, 64, 83); //Anti-aliasing
}

/**
** @brief
** allocate memory for buffers
** compile opencl program
** @param cl_program
** @return ** int
*/
int		init_kernel(t_cl_program *program, t_scene *scene, t_sampler_manager *sampler_manager)
{
	int		ret = 0;

	/*init buffers for kernel*/
	init_buffers(program, scene, sampler_manager);
	cl_error(program, &program->clp, ret);
	program->program = create_program(program->clp.context);
	/* build kernel program */
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
		DEFAULT_KERNEL_INCLUDE, NULL, NULL);
	cl_error(program, &program->clp, ret);
	/* create kernel */
	program->kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
		&ret);
	cl_error(program, &program->clp, ret);
	ft_clerror(program->clp.ret);
	return (0);
}

/**
** @brief
** default initialization
** @param window
** @param cl_program
** @return ** int
*/
int		init_rt(t_rt *rt, char *scene_file)
{
	init_cl(&rt->program.clp);
	init_sampler_manager(&rt->sampler_manager);
	init_window(&rt->window);
	rt->program.work_size = DEFAULT_WORK_SIZE;
	rt->program.work_group_size = WORK_GROUP_SIZE;
	init_options(&rt->options, &rt->sampler_manager);
	// init_sampler(&rt->sampler);
	read_data(&rt->scene, &rt->sampler_manager, scene_file); //split to init default scene and read file
	init_kernel(&rt->program, &rt->scene, &rt->sampler_manager);

	return 0;
}
