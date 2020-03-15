/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/03/15 23:25:00 by dmelessa         ###   ########.fr       */
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

void	start_render_kernel(t_cl_program *program,
							t_scene *scene,
							uint32_t *image,
							t_renderer renderer)
{
	int			err_code;

	err_code = 0;
	clSetKernelArg(program->kernel, 0, sizeof(cl_mem), &program->output_image);
	clSetKernelArg(program->kernel, 1, sizeof(cl_mem), &program->objects);
	clSetKernelArg(program->kernel, 2, sizeof(cl_int), &scene->nobjects);
	clSetKernelArg(program->kernel, 3, sizeof(cl_mem), &program->triangles);
	clSetKernelArg(program->kernel, 4, sizeof(cl_int), &scene->ntriangles);
	clSetKernelArg(program->kernel, 5, sizeof(cl_mem), &program->lights);
	clSetKernelArg(program->kernel, 6, sizeof(cl_int), &scene->nlights);
	clSetKernelArg(program->kernel, 7, sizeof(t_camera), &scene->camera);
	clSetKernelArg(program->kernel, 8, sizeof(t_light), &scene->ambient_light);
	clSetKernelArg(program->kernel, 9, sizeof(t_render_options),
												&renderer.options);
	clSetKernelArg(program->kernel, 10, sizeof(cl_mem), &program->samples);

	err_code = clEnqueueNDRangeKernel(program->clp.queue, program->kernel, 1,
		NULL, &program->work_size, &program->work_group_size, 0, NULL, NULL);
	assert(!err_code);
	err_code = clEnqueueReadBuffer(program->clp.queue, program->output_image,
		CL_TRUE, 0, program->work_size * sizeof(uint32_t),
		image, 0, NULL, NULL);
	assert(!err_code);
}

float	rand_float()
{
	return ((float)rand() / (float)RAND_MAX);
}

cl_float2	*generate_samples(t_render_options options)
{
	int			n = sqrtf(options.sampler_info.num_samples);
	int			index[3];
	int			pepa;
	cl_float2	*sp;

	pepa = 0;
	sp = malloc(sizeof(cl_float2) * options.sampler_info.num_sets * options.sampler_info.num_samples);
	for (index[0] = 0; index[0] < options.sampler_info.num_sets; index[0]++)
	{
		for (index[1] = 0; index[1] < n; index[1]++)
		{
			for (index[2] = 0; index[2] < n; index[2]++)
			{
				sp[pepa].x = (index[1] + rand_float()) / n;
				sp[pepa].y = (index[2] + rand_float()) / n;
				pepa++;
				printf("%d: %f %f\n",pepa, sp[pepa - 1].x, sp[pepa - 1].y);
			}
		}
	}
	return sp;
}

void	copy_to_device(t_cl_program program, cl_float2 *sampler_sets, t_render_options options)
{
	int	ret;
	program.samples = clCreateBuffer(program.clp.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(cl_float2) * options.sampler_info.num_sets * options.sampler_info.num_samples, sampler_sets, &ret);
	cl_error(&program, &program.clp, ret);
}

int		main(int ac, char **av)
{
	t_window		window;
	t_cl_program	program;
	t_scene			scene;
	t_renderer		renderer;
	int				value;

	init_rt(&window, &program, &scene, &renderer);

	while (1)
	{
		value = catch_event(&renderer);
		if (value == 1)
			break;
		else if (value == 0)
		{
			start_render_kernel(&program, &scene, window.image, renderer);
			display_image(&window);
		}
	}
	exit_program(window);
	return (0);
}
