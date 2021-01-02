/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_keydown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:00:55 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/21 13:31:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "state.h"

static int			catch_keydown_04(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_p)
	{
		rt->options.shadows = !rt->options.shadows;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_a)
	{
		move_camera(&rt->scene.camera, 0, -interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		rotate_camera(&rt->scene.camera, 0, interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_ESCAPE)
		return (exit_state);
	return (render_state);
}

static int			catch_keydown_03(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_q)
	{
		rotate_camera(&rt->scene.camera, 2, -interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_e)
	{
		rotate_camera(&rt->scene.camera, 2, interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_TAB)
	{
		if (g_objects_tab_pressed)
			interface->current_instance_id++;
		if (g_camera_tab_pressed)
			interface->current_light_id++;
		return (update_gui_state);
	}
	return (catch_keydown_04(rt, interface, event));
}

static int			catch_keydown_02(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
	{
		rotate_camera(&rt->scene.camera, 0, -interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		rotate_camera(&rt->scene.camera, 1, -interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		rotate_camera(&rt->scene.camera, 1, interface->rotation_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	return (catch_keydown_03(rt, interface, event));
}

static int			catch_keydown_01(t_rt *rt, t_interface *interface,
							SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_d)
	{
		move_camera(&rt->scene.camera, 0, interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_SPACE)
	{
		move_camera(&rt->scene.camera, 1, interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_LCTRL)
	{
		move_camera(&rt->scene.camera, 1, -interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	return (catch_keydown_02(rt, interface, event));
}

int					catch_keydown(t_rt *rt, t_interface *interface,
									SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_r)
	{
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_w)
	{
		move_camera(&rt->scene.camera, 2, -interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_s)
	{
		move_camera(&rt->scene.camera, 2, interface->movement_step);
		rt->options.reset = 1;
		rt->options.spp = NUM_SAMPLES;
		return (render_state);
	}
	if (event.key.keysym.sym == SDLK_F10)
		SDL_SetRelativeMouseMode(interface->relative_mouse = TRUE);
	if (event.key.keysym.sym == SDLK_F11)
		SDL_SetRelativeMouseMode(interface->relative_mouse = FALSE);
	return (catch_keydown_01(rt, interface, event));
}
