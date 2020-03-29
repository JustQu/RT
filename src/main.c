/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/03/29 18:17:13 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"
# include "stdlib.h"

/**
** @brief
** L1 Cache = Local Memory(OpenCL) = Shared Memory(CUDA)
*/

void	exit_program(t_window window)
{
/*
    err = clFlush(command_queue);
    err = clFinish(command_queue);
    err = clReleaseKernel(kernel);
    err = clReleaseProgram(program);
    err = clReleaseMemObject(img_cl);
    err = clReleaseMemObject(obj_cl);
    err = clReleaseCommandQueue(command_queue);
    err = clReleaseContext(context);*/
	SDL_DestroyTexture(window.texture);
	SDL_DestroyRenderer(window.renderer);
	SDL_DestroyWindow(window.ptr);
	SDL_Quit();
}

/**
** @brief
** dispay image in window w
** @param w
** @return ** void
*/
void	display_image(t_window *w)
{
	SDL_UpdateTexture(w->texture, NULL, w->image, sizeof(uint32_t) * w->width);
	SDL_RenderClear(w->renderer);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
	SDL_RenderPresent(w->renderer);
}

void	start_render_kernel(t_rt rt)
{
	int			err_code;

	err_code = 0;
	// printf("ARgs\n");
	clSetKernelArg(rt.program.kernel, 0, sizeof(cl_mem),
													&rt.program.output_image);
	clSetKernelArg(rt.program.kernel, 1, sizeof(cl_mem),
													&rt.program.objects);
	clSetKernelArg(rt.program.kernel, 2, sizeof(cl_int),
													&rt.scene.nobjects);
	clSetKernelArg(rt.program.kernel, 3, sizeof(cl_mem),
													&rt.program.triangles);
	clSetKernelArg(rt.program.kernel, 4, sizeof(cl_int),
													&rt.scene.ntriangles);
	clSetKernelArg(rt.program.kernel, 5, sizeof(cl_mem),
													&rt.program.lights);
	clSetKernelArg(rt.program.kernel, 6, sizeof(cl_int),
													&rt.scene.nlights);
	clSetKernelArg(rt.program.kernel, 7, sizeof(t_camera),
													&rt.scene.camera);
	clSetKernelArg(rt.program.kernel, 8, sizeof(t_light),
													&rt.scene.ambient_light);
	clSetKernelArg(rt.program.kernel, 9, sizeof(t_render_options),
													&rt.options);
	clSetKernelArg(rt.program.kernel, 10, sizeof(t_sampler_info),
													&rt.sampler.info);
	clSetKernelArg(rt.program.kernel, 11, sizeof(cl_mem),
													&rt.program.samples);
	err_code = clEnqueueNDRangeKernel(rt.program.clp.queue, rt.program.kernel,
		1, NULL, &rt.program.work_size, &rt.program.work_group_size, 0, NULL, NULL);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(rt.program.clp.queue,
		rt.program.output_image, CL_TRUE, 0, rt.program.work_size *
		sizeof(uint32_t), rt.window.image, 0, NULL, NULL);
	cl_error(&rt.program, &rt.program.clp, err_code);
	assert(!err_code);
}

int		main(int ac, char **av)
{
	t_rt	rt;
	int		value;

	init_rt(&rt, av[1]);
	while (1)
	{
		value = catch_event(&rt);
		if (value == 1)
			break;
		else if (value == 0)
		{
			start_render_kernel(rt);
			display_image(&rt.window);
		}
	}
	exit_program(rt.window);
	return (0);
}
