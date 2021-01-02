/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 23:21:28 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:20:07 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int				is_press_button(SDL_Event *event, SDL_Rect *rect)
{
	if (event->motion.y >= rect->y
		&& event->motion.y <= rect->y + rect->h
		&& event->motion.x >= rect->x && event->motion.x <= rect->x + rect->w)
		return (1);
	else
		return (0);
}

t_s32			catch_tab_bar1(SDL_Event *event, t_all_rect *rect)
{
	if (is_press_button(event, &rect->tab_objects_button))
	{
		g_camera_tab_pressed = 0;
		g_objects_tab_pressed = 1;
		g_options_tab_pressed = 0;
		return (update_gui_state);
	}
	if (is_press_button(event, &rect->tab_options_button))
	{
		g_camera_tab_pressed = 0;
		g_objects_tab_pressed = 0;
		g_options_tab_pressed = 1;
		return (update_gui_state);
	}
	return (render_state);
}

t_s32			catch_tab_bar(SDL_Event *event, t_all_rect *rect)
{
	if (is_press_button(event, &rect->title_button)
		|| event->key.keysym.sym == SDLK_m)
	{
		g_show_gui ^= 1;
		return (update_gui_state);
	}
	if (is_press_button(event, &rect->save_img_button)
		&& g_camera_tab_pressed == 1)
	{
		g_save_image = 1;
		return (update_gui_state);
	}
	if (is_press_button(event, &rect->tab_camera_button))
	{
		g_camera_tab_pressed = 1;
		g_objects_tab_pressed = 0;
		g_options_tab_pressed = 0;
		return (update_gui_state);
	}
	return (catch_tab_bar1(event, rect));
}

static int		catch_window_event(t_window *win, SDL_Event event)
{
	if (event.window.event == SDL_WINDOWEVENT_SHOWN)
		;
	else if (event.window.event == SDL_WINDOWEVENT_HIDDEN)
		;
	else if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MOVED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
		;
	else if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		return (exit_state);
	else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		win->width = event.window.data1;
		win->height = event.window.data2;
		return (update_gui_state);
	}
	return (render_state);
}

/*
** @todo:  translate window coordinates in image coordinates,
** e.g. windos is 1200x600 and image is 1920x1080//
** then we need x * IMG_W/WIN_W  and y * IMG_H/WIN_H
**
** @param rt
** @param win
** @param interface
** @return ** int
*/

int				catch_event(t_rt *rt, t_window *win, t_interface *interface)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (exit_state);
		if (event.type == SDL_WINDOWEVENT)
			return (catch_window_event(win, event));
		if (event.type == SDL_KEYDOWN)
			return (catch_keydown(rt, interface, event));
		if (event.type == SDL_MOUSEBUTTONDOWN)
			return (catch_tab_bar(&event, &interface->gui.all_rect));
		if (event.type == SDL_MOUSEMOTION)
			if (interface->relative_mouse == TRUE)
			{
				rotate_camera(&rt->scene.camera, 1, event.motion.xrel *
								interface->rotation_step);
				rotate_camera(&rt->scene.camera, 0, event.motion.yrel *
								interface->rotation_step);
				rt->options.reset = 1;
				rt->options.spp = NUM_SAMPLES;
			}
		return (-1);
	}
	return (render_state);
}
