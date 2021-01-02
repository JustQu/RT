/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:21:45 by alex              #+#    #+#             */
/*   Updated: 2020/12/21 17:34:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "window.h"
#include <math.h>

void			utils_call_option_tab(t_window *win, t_gui *gui, char **str)
{
	get_rt_type_data(gui->options.tracer_type, "Type RT", str);
	draw_button(win, &gui->all_rect.first_button, str, &gui->colors);
	free_str(str);
	get_illumin_data(gui->options.ambient_illumination, "Ambient type", str);
	draw_button(win, &gui->all_rect.second_button, str, &gui->colors);
	free_str(str);
}

void			util_call_object_tab(t_window *win, t_gui *gui, char **str)
{
	get_shape_data(gui->current_instance.type, "Shape", str);
	draw_button(win, &gui->all_rect.first_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.origin, "Origin", str);
	draw_button_xyz(win, &gui->all_rect.second_button, str, &gui->colors);
	free_str(str);
}

void			util_call_camera_tab(t_window *win, t_gui *gui, char **str)
{
	get_camera_type_data(gui->camera.type, "Type camera", str);
	draw_button(win, &gui->all_rect.first_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->camera.origin, "Position", str);
	draw_button_xyz(win, &gui->all_rect.second_button, str, &gui->colors);
	free_str(str);
}

void			option_tab_cont(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	get_float_data((float)gui->options.ambient_illumination, "Ambient_il", str);
	draw_button(win, &gui->all_rect.fourth_button, str, &gui->colors);
	free_str(str);
	type_ambien_il(win, gui);
	draw_line(win, &gui->colors, gui->all_rect.background,
				gui->all_rect.sixth_button);
	get_true_data(gui->options.shadows, "Shadows", str);
	draw_button(win, &gui->all_rect.seven_button, str, &gui->colors);
	free_str(str);
	get_float_data((float)gui->options.depth, "Depth", str);
	draw_button(win, &gui->all_rect.eight_button, str, &gui->colors);
	free_str(str);
}

void			draw_color_button(t_window *win, t_colors *color,
					t_color fill_color, SDL_Rect *rect)
{
	SDL_Rect	button;

	SDL_SetRenderDrawColor(win->renderer, (t_u8)(sqrtf(fill_color.r) * 255.0f),
						(t_u8)(sqrtf(fill_color.g) * 255.0f),
						(t_u8)(sqrtf(fill_color.b) * 255.0f),
						(t_u8)(sqrtf(fill_color.a) * 255.0f));
	button = init_rect_size(rect->x + MARGIN, rect->y,
							rect->w - MARGIN * 2 - 150, rect->h);
	SDL_RenderFillRect(win->renderer, &button);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, &button);
}
