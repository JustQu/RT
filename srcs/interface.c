/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:01:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/22 00:12:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "resource_manager.h"

void	init_interface(t_interface *const interface, int mode, int enable_gui)
{
	interface->mode = mode;
	interface->enable_gui = enable_gui;
	interface->current_instance_id = 7;
	interface->current_light_id = 0;
	interface->relative_mouse = FALSE;
	interface->movement_step = 0.1f;
	interface->rotation_step = 1.0f;
}

void	display_info(t_interface *const interface,
					t_res_mngr *const mngr,
					t_window *const window)
{
	interface->current_instance = get_instance_info(mngr,
								interface->current_instance_id);
	interface->current_light = get_light_info(mngr,
								interface->current_light_id);
	interface->camera = mngr->scene->camera;
	interface->options = *mngr->rt_options;
	if (interface->mode == window_mode)
	{
		if (interface->enable_gui == TRUE)
		{
			interface->gui.current_instance = interface->current_instance;
			interface->gui.current_light = interface->current_light;
			interface->gui.camera = interface->camera;
			interface->gui.options = interface->options;
			gui(window, &interface->gui);
		}
	}
}
