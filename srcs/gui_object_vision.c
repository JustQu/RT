/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_vision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:50 by alex              #+#    #+#             */
/*   Updated: 2020/12/29 15:25:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			gui_cone_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.e, "Angle", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.height, "Height", str);
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_cylinder_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.r, "Radius", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.height, "Height", str);
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_torus_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float_data(gui->current_instance.r2, "Small Radius", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_instance.r, "Radius", str);
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_box_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float4_data(gui->current_instance.v1, "minimum", str);
	draw_button_xyz(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.v2, "maximum", str);
	draw_button_xyz(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			gui_rectangle_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float4_data(gui->current_instance.v1, "Side a", str);
	draw_button_xyz(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.v2, "Side b", str);
	draw_button_xyz(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}
