/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/04/26 21:23:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"
# include "stdlib.h"

/**
** @brief
** L1 Cache = Local Memory(OpenCL) = Shared Memory(CUDA)
*/
void	print_vector(cl_float4 vec)
{
	printf("(%.1f, %.1f, %.1f)", vec.x, vec.y, vec.z);
}


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

void	write_buffers(t_rt rt)
{
	clEnqueueWriteBuffer(rt.program.clp.queue, rt.program.samplers,
		CL_FALSE, 0, sizeof(t_sampler) * rt.sampler_manager.count,
		rt.sampler_manager.samplers, 0, 0, 0);
}

void	set_kernel_args(t_rt rt)
{
	cl_kernel	k;
	int			err_code;

	k = rt.program.kernel;
	// write_buffers(rt);
	clSetKernelArg(k, 0, sizeof(cl_mem), &rt.program.output_image);
	clSetKernelArg(k, 1, sizeof(cl_mem), &rt.program.objects);
	clSetKernelArg(k, 2, sizeof(cl_int), &rt.scene.nobjects);
	clSetKernelArg(k, 3, sizeof(cl_mem), &rt.program.triangles);
	clSetKernelArg(k, 4, sizeof(cl_int), &rt.scene.ntriangles);
	clSetKernelArg(k, 5, sizeof(cl_mem), &rt.program.lights);
	clSetKernelArg(k, 6, sizeof(cl_int), &rt.scene.nlights);
	clSetKernelArg(k, 7, sizeof(t_camera), &rt.scene.camera);
	clSetKernelArg(k, 8, sizeof(t_light), &rt.scene.ambient_light);
	clSetKernelArg(k, 9, sizeof(t_render_options), &rt.options);
	clSetKernelArg(k, 10, sizeof(cl_mem), &rt.program.samplers);
	clSetKernelArg(k, 11, sizeof(cl_mem), &rt.program.samples);
	clSetKernelArg(k, 12, sizeof(cl_mem), &rt.program.disk_samples);
	clSetKernelArg(k, 13, sizeof(cl_mem), &rt.program.hemisphere_samples);

}

void	start_render_kernel(t_rt rt)
{
	int			err_code;

	err_code = 0;
	set_kernel_args(rt);
	err_code = clEnqueueNDRangeKernel(rt.program.clp.queue, rt.program.kernel,
		1, NULL, &rt.program.work_size, &rt.program.work_group_size, 0, NULL, NULL);
	// printf("%d\n", err_code);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(rt.program.clp.queue,
		rt.program.output_image, CL_FALSE, 0, rt.program.work_size *
		sizeof(uint32_t), rt.window.image, 0, NULL, NULL);
	cl_error(&rt.program, &rt.program.clp, err_code);
	assert(!err_code);
}

void cleanup(t_rt rt)
{
	clReleaseKernel(rt.program.kernel);
	clReleaseProgram(rt.program.program);
	// clReleaseMemObject(rt.program.disk_samples);
	clReleaseMemObject(rt.program.samplers);
	// clReleaseMemObject(rt.program.hemisphere_samples);
	clReleaseMemObject(rt.program.samples);
	clReleaseMemObject(rt.program.lights);
	clReleaseMemObject(rt.program.objects);
	clReleaseMemObject(rt.program.output_image);
	clReleaseMemObject(rt.program.triangles);
	clReleaseCommandQueue(rt.program.clp.queue);
	clReleaseContext(rt.program.clp.context);
	free(rt.scene.triangles);
	free(rt.scene.lights);
	free(rt.scene.objects);
	free(rt.window.image);
}
// #include "windows.h"

int		main(int ac, char **av)
{
	t_rt	rt;
	int		value;
	// Sleep(1000);
	srand(999);
	ac == 1 ? init_rt(&rt, NULL) : init_rt(&rt, av[1]);
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
	cleanup(rt);
	exit_program(rt.window);
	return (0);
}
