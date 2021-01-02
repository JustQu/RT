/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ocl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:59:58 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:25:17 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_ocl.h"
#include "app.h"
#include "rt_error.h"
#include "image.h"

static int	init_clp(t_clp *clp, cl_device_type dev_type)
{
	cl_platform_id	pl_id;
	cl_uint			nde;

	pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &pl_id, NULL);
	rt_is_dead(opencl_err, cl_get_platform_id_error, clp->ret, "");
	clp->ret = clGetDeviceIDs(pl_id, dev_type, 1, &clp->de_id, &nde);
	rt_is_dead(opencl_err, cl_get_device_id_error, clp->ret, "");
	clp->context = clCreateContext(NULL, 1, &clp->de_id, NULL, NULL, &clp->ret);
	rt_is_dead(opencl_err, cl_create_context_error, clp->ret, "");
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &clp->ret);
	rt_is_dead(opencl_err, cl_create_command_queue_error, clp->ret, "");
	return (0);
}

/*
** @note: get work group info from KernelWorkGroupInfo
**
** clGetKernelWorkGroupInfo(p->new_kernel, p->info.de_id,
** 						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &a, NULL);
** fprintf(stdout, "Work group kernel - %zd\n", a);
**
** @param p
** @param window
** @param image
** @return ** int
*/

static int	init_kernel(t_cl_program *p, t_window *window, t_image *image)
{
	int		r;

	r = 0;
	p->work_size = image->width * image->height;
	p->work_group_size = WORK_GROUP_SIZE;
	p->program = create_program(p->info.context);
	loading_screen(p, window);
	p->new_kernel = clCreateKernel(p->program, KERNEL_NAME, &r);
	cl_error(p, &p->info, r);
	p->help_kernel = clCreateKernel(p->program, "translate_image", &r);
	return (r);
}

int			init_ocl(t_cl_program *const program,
					t_window const *const window,
					t_image *const image,
					cl_device_type const device_type)
{
	init_clp(&program->info, device_type);
	init_kernel(program, (t_window *)window, image);
	return (SUCCESS);
}
