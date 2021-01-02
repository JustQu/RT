/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:15:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "gui.h"

/*
** @brief
**
** @todo: parse command line arguments
** @param app
** @param ac
** @param av
** @return ** int
*/

int		init_app(t_app *app)
{
	if (app->options.mode != console)
		init_window(&app->window, app->options.window_width,
					app->options.window_height);
	init_image(&app->image, app->options.image_width,
				app->options.image_height, app->options.image_file);
	init_interface(&app->interface, app->options.mode, app->options.enable_gui);
	init_gui(&app->interface.gui, app->window);
	init_resource_manager(&app->resource_manager, &app->rt);
	init_rt(app);
	app->rt.scene.camera.viewplane.width = app->image.width;
	app->rt.scene.camera.viewplane.height = app->image.height;
	return (SUCCESS);
}
