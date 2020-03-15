/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/03/15 23:21:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int catch_event(t_renderer *renderer)
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
			}
			break;
			}
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return 1;
			else if (event.key.keysym.sym == SDLK_p)
			{
				renderer->options.shadows = !renderer->options.shadows;
			}
		}
		if (event.type == SDL_KEYUP)
		{
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			printf("Mouse press at %d %d", event.button.x, event.button.y);
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
		}
		//check input
		//switch kernel here?
		return -1;
	}
	return 0;
}
