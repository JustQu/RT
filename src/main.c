/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/10 18:29:59 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

/**
** @brief
** L1 Cache = Local Memory(OpenCL) = Shared Memory(CUDA)
*/

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

int		catch_event()
{
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return 1;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_MOVED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;
				case SDL_WINDOWEVENT_CLOSE:
					return 1;

				case SDL_WINDOWEVENT_RESIZED:
				{
					printf("Window size changed to %dx%d\n",
							event.window.data1, event.window.data2);
				} break;

			}
		}
		if (event.type == SDL_KEYDOWN)
		{

		}
		if (event.type == SDL_KEYUP)
		{

		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{

		}
		//check input
		//switch kernel here?
	}
	return 0;
}



void	render_loop()
{
	t_window		window;
	t_cl_program	program;
	t_scene			scene;
	t_bool			quit;

	quit = FALSE;
	init(&window, &program, &scene);
	while (!quit)
	{
		if (catch_event() == 1)
			quit = TRUE;
		clSetKernelArg(program.kernel, 0, sizeof(cl_mem),
			(void *)&program.output);
		clEnqueueNDRangeKernel(program.clp.queue, program.kernel, 1, NULL,
			&program.work_size, &program.work_group_size, 0, NULL, NULL);
		clEnqueueReadBuffer(program.clp.queue, program.output, CL_TRUE, 0,
			program.work_size * sizeof(uint32_t), window.image, 0, NULL, NULL);
		display_image(&window);
	}
}

int main(void)
{
	render_loop();
	SDL_Quit();
	return (0);
}
