/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 00:15:25 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/22 00:17:41 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void		gui_material_type3(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->current_instance.material.type == plastic)
	{
		get_float_data(gui->current_instance.material.kd, "diffuseness", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
		get_float_data(gui->current_instance.material.kr, "reflectivity", str);
		draw_button(win, &gui->all_rect.ten_button, str, &gui->colors);
		free_str(str);
		get_float_data(gui->current_instance.material.exp, "roughness", str);
		draw_button(win, &gui->all_rect.eleven_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_instance.material.type == mirror)
	{
		get_float_data(gui->current_instance.material.kr, "reflectivity", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
}

static void		gui_material_type2(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->current_instance.material.type == emissive)
	{
		get_float_data(gui->current_instance.material.ls, "Intensivity", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_instance.material.type == matte)
	{
		get_float_data(gui->current_instance.material.kd, "diffuse", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
	}
	gui_material_type3(win, gui);
}

void			gui_material_type(t_window *win,
									t_gui *gui)
{
	char		*str[4];

	if (gui->current_instance.material.type == conductor)
	{
		get_float_data(gui->current_instance.material.kr, "reflectivity", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
		get_float_data(gui->current_instance.material.exp, "roughness", str);
		draw_button(win, &gui->all_rect.ten_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_instance.material.type == dielectric)
	{
		get_float_data(gui->current_instance.material.kt, "transparency", str);
		draw_button(win, &gui->all_rect.nine_button, str, &gui->colors);
		free_str(str);
		get_float_data(gui->current_instance.material.exp, "roughness", str);
		draw_button(win, &gui->all_rect.ten_button, str, &gui->colors);
		free_str(str);
	}
	gui_material_type2(win, gui);
}
