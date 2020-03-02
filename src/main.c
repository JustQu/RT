/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/16 18:17:27 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

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

void	start_render_kernel(t_cl_program *program,
							t_scene *scene,
							uint32_t *image)
{
	int	err_code;

	err_code = 0;
	clSetKernelArg(program->kernel, 0, sizeof(cl_mem), (void *)&program->output_image);
	clSetKernelArg(program->kernel, 1, sizeof(cl_mem), (void *)&program->objects);
	clSetKernelArg(program->kernel, 2, sizeof(cl_int),
		(void *)&scene->nobjects);
	clSetKernelArg(program->kernel, 3, sizeof(t_camera), &scene->camera);
	clSetKernelArg(program->kernel, 4, sizeof(cl_mem), (void *)&program->triangles);
	err_code = clEnqueueNDRangeKernel(program->clp.queue, program->kernel, 1,
		NULL, &program->work_size, &program->work_group_size, 0, NULL, NULL);
	ft_clerror(err_code);
	err_code = clEnqueueReadBuffer(program->clp.queue, program->output_image,
		CL_TRUE, 0, program->work_size * sizeof(uint32_t),
		image, 0, NULL, NULL);
	ft_clerror(err_code);
}

int		main(int ac, char **av)
{
	t_window		window;
	t_cl_program	program;
	t_scene			scene;
	t_bool			quit;

	quit = FALSE;
	if (ac != 2)
	{
		ft_putendl_fd("usage: ./RT [scene.scene]", 2);
		return (-1);
	}
	init(&window, &program, &scene, av[1]);


	/* delete all of next printf */
	printf("obj = %d; tri = %d\n", scene.nobjects, scene.ntriangles);//delete later
	printf("cam: origin");
	print_vector(scene.camera.origin);
	printf(" direction");
	print_vector(scene.camera.direction);
	printf(" fov(%d)\n", scene.camera.fov);
	for (int n = 0; n < scene.nobjects; n++)
	{
		t_obj obj = scene.objects[n];
		printf("%s: r(%.1f) r2(%.1f) angle(%.3f) maxm(%.1f) minm(%.1f)\n",
		 scene.obj_name[obj.type], obj.r, obj.r2, obj.angle, obj.maxm, obj.minm);
	}


	start_render_kernel(&program, &scene, window.image);
	display_image(&window);
	while (!quit)
	{
		if (catch_event() == 1)
			quit = TRUE;
	}
	exit_program(window);
	return (0);
}
