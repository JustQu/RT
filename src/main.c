/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/03/09 22:34:46 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

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

void	start_render_kernel(t_cl_program *program,
							t_scene *scene,
							uint32_t *image)
{
	int	err_code;

	err_code = 0;
	clSetKernelArg(program->kernel, 0, sizeof(cl_mem), (void *)&program->output_image);
	clSetKernelArg(program->kernel, 1, sizeof(cl_mem),
		(void *)&program->objects);
	clSetKernelArg(program->kernel, 2, sizeof(cl_int),
		(void *)&scene->nobjects);
	clSetKernelArg(program->kernel, 3, sizeof(cl_mem),
		(void *)&program->lights);
	clSetKernelArg(program->kernel, 4, sizeof(cl_int), (void *)&scene->nlights);
	clSetKernelArg(program->kernel, 5, sizeof(t_camera), &scene->camera);
	clSetKernelArg(program->kernel, 6, sizeof(t_light), &scene->ambient_light);
	clSetKernelArg(program->kernel, 7, sizeof(cl_mem),
		(void *)&program->triangles);
	err_code = clEnqueueNDRangeKernel(program->clp.queue, program->kernel, 1,
		NULL, &program->work_size, &program->work_group_size, 0, NULL, NULL);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(program->clp.queue, program->output_image,
		CL_TRUE, 0, program->work_size * sizeof(uint32_t),
		image, 0, NULL, NULL);
	assert(!err_code);
}

int		main(int ac, char **av)
{
	t_window		window;
	t_cl_program	program;
	t_scene			scene;
	t_bool			quit;
	int				value;
	quit = FALSE;
	init(&window, &program, &scene);
	while (!quit)
	{
		value = catch_event();
		if (value == 1)
			quit = TRUE;
		else if (value == 0)
		{
			start_render_kernel(&program, &scene, window.image);
			display_image(&window);
		}
	}
	exit_program(window);
	return (0);
}
