/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:19:50 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

/*
** @brief
** dispay image in window w
** @param w
** @return ** void
*/

void		display_image(t_window *w, t_image *image)
{
	SDL_RenderClear(w->renderer);
	SDL_UpdateTexture(w->texture, NULL, image->pixels,
					sizeof(*image->pixels) * image->width);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
}

void		render_image(t_app app)
{
	int		err_code;

	err_code = 0;
	render_scene(app.rt);
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 0,
								sizeof(cl_mem), &app.rt.ocl_program.rgb_image);
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 1,
							sizeof(cl_mem), &app.rt.ocl_program.output_image);
	err_code |= clSetKernelArg(app.rt.ocl_program.help_kernel, 2,
								sizeof(cl_float), &app.rt.options.spp);
	rt_is_dead(opencl_err, cl_kernel_arg_error, err_code, "main.c 1");
	err_code = clEnqueueNDRangeKernel(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.help_kernel, 1, NULL, &app.rt.ocl_program.work_size,
		&app.rt.ocl_program.work_group_size, 0, NULL, NULL);
	rt_is_dead(opencl_err, cl_kernel_start_error, err_code, "main.c 2");
	err_code = clEnqueueReadBuffer(app.rt.ocl_program.info.queue,
		app.rt.ocl_program.output_image, CL_TRUE, 0,
		app.image.width * app.image.height * sizeof(uint32_t),
		app.image.pixels, 0, NULL, NULL);
	rt_is_dead(opencl_err, cl_read_buffer_error, err_code, "main.c 3");
}

static void	window_render_loop(t_app *const app)
{
	int	state;

	state = render_state;
	while (state != exit_state)
	{
		state = catch_event(&app->rt, &app->window, &app->interface);
		if (state == render_state)
		{
			render_image(*app);
			display_image(&app->window, &app->image);
			app->rt.options.spp += 1;
			app->rt.options.reset = 0;
			save_image_func(&app->window, &app->image);
			display_info(&app->interface, &app->resource_manager,
						&app->window);
			SDL_RenderPresent(app->window.renderer);
		}
		else if (state == update_gui_state)
		{
			init_rect(&app->interface.gui.all_rect, &app->window);
			display_info(&app->interface, &app->resource_manager,
						&app->window);
			SDL_RenderPresent(app->window.renderer);
		}
	}
}

static void	console_render_loop(t_app *const app)
{
	int	i;

	i = 0;
	while (i < app->options.num_samples)
	{
		if (i > 1)
			app->rt.options.reset = 0;
		render_image(*app);
		app->rt.options.spp += 1;
		ft_putstr("\rRendering in progress ");
		ft_putnbr((int)(i * 100.0f / app->options.num_samples));
		ft_putstr("%");
		save_image_func(&app->window, &app->image);
		i++;
	}
	ft_putendl("");
	ft_putendl("Done!");
	g_save_image = 1;
	save_image_func(&app->window, &app->image);
}

/*
** @brief
** NOTE: leaks: (stdout, "is leaked?: %d", _CrtDumpMemoryLeaks());
** @param ac
** @param av
** @return ** int
*/

int			main(int ac, char **av)
{
	t_app		app;

	read_av(&app, ac, av);
	init_app(&app);
	if (app.options.mode == window_mode)
	{
		window_render_loop(&app);
	}
	else
	{
		console_render_loop(&app);
	}
	cleanup(app);
	SDL_Quit();
	return (SUCCESS);
}
