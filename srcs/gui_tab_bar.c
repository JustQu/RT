/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_tab_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:03:59 by user              #+#    #+#             */
/*   Updated: 2020/12/21 13:34:28 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"
#include "libft.h"

void			camera_tab(t_window *win, t_gui *gui)
{
	char		*str[4];

	render_tab_bar(win, &gui->colors.text_color,
	&gui->all_rect.tab_camera_button, "Camera");
	SDL_SetRenderDrawColor(win->renderer, gui->colors.text_color.r,
	gui->colors.text_color.g, gui->colors.text_color.b,
	gui->colors.text_color.a);
	SDL_RenderDrawLine(win->renderer, gui->all_rect.tab_camera_button.x,
	gui->all_rect.tab_camera_button.y + gui->all_rect.tab_camera_button.h,
	gui->all_rect.tab_camera_button.x + gui->all_rect.tab_camera_button.w,
	gui->all_rect.tab_camera_button.y + gui->all_rect.tab_camera_button.h);
	util_call_camera_tab(win, gui, str);
	get_float4_data(gui->camera.w, "Direction", str);
	draw_button_xyz(win, &gui->all_rect.third_button, str, &gui->colors);
	free_str(str);
	get_str_data("save", "Save image", str);
	draw_button(win, &gui->all_rect.fourth_button, str, &gui->colors);
	free_str(str);
	get_void_data("Light", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	light_tab(win, gui);
}

void			objects_tab(t_window *win, t_gui *gui)
{
	char		*str[4];

	render_tab_bar(win, &gui->colors.text_color,
	&gui->all_rect.tab_objects_button, "Objects");
	SDL_SetRenderDrawColor(win->renderer, gui->colors.text_color.r,
	gui->colors.text_color.g, gui->colors.text_color.b,
	gui->colors.text_color.a);
	SDL_RenderDrawLine(win->renderer, gui->all_rect.tab_objects_button.x,
	gui->all_rect.tab_objects_button.y + gui->all_rect.tab_objects_button.h,
	gui->all_rect.tab_objects_button.x + gui->all_rect.tab_objects_button.w,
	gui->all_rect.tab_objects_button.y + gui->all_rect.tab_objects_button.h);
	util_call_object_tab(win, gui, str);
	get_float4_data(gui->current_instance.rotation, "Rotation", str);
	draw_button_xyz(win, &gui->all_rect.third_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.scaling, "Scalling", str);
	draw_button_xyz(win, &gui->all_rect.fourth_button, str, &gui->colors);
	free_str(str);
	objects_tab_cont(win, gui);
}

void			light_tab(t_window *win,
					t_gui *gui)
{
	char		*str[4];

	SDL_SetRenderDrawColor(win->renderer, gui->colors.text_color.r,
	gui->colors.text_color.g, gui->colors.text_color.b,
		gui->colors.text_color.a);
	SDL_RenderDrawLine(win->renderer, gui->all_rect.tab_camera_button.x,
		gui->all_rect.fifth_button.y + gui->all_rect.fifth_button.h,
		gui->all_rect.fifth_button.x + gui->all_rect.fifth_button.w,
		gui->all_rect.fifth_button.y + gui->all_rect.fifth_button.h);
	get_intensive_data(gui->current_light.type, "Type", str);
	draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
	get_float_data(gui->current_light.ls, "Intensity", str);
	draw_button(win, &gui->all_rect.seven_button, str, &gui->colors);
	is_type_lights(win, gui);
	free_str(str);
}

void			option_tab(t_window *win,
					t_gui *gui)
{
	char	*str[4];

	render_tab_bar(win, &gui->colors.text_color,
	&gui->all_rect.tab_options_button, "Options");
	SDL_SetRenderDrawColor(win->renderer, gui->colors.text_color.r,
	gui->colors.text_color.g, gui->colors.text_color.b,
	gui->colors.text_color.a);
	SDL_RenderDrawLine(win->renderer, gui->all_rect.tab_options_button.x,
	gui->all_rect.tab_options_button.y + gui->all_rect.tab_options_button.h,
	gui->all_rect.tab_options_button.x + gui->all_rect.tab_options_button.w,
	gui->all_rect.tab_options_button.y + gui->all_rect.tab_options_button.h);
	utils_call_option_tab(win, gui, str);
	get_color_data(gui->options.background_color, "Back color", str);
	free(str[1]);
	str[1] = NULL;
	draw_button(win, &gui->all_rect.third_button, str, &gui->colors);
	draw_color_button(win, &gui->colors, gui->options.background_color,
	&gui->all_rect.third_button);
	draw_line(win, &gui->colors, gui->all_rect.background,
	gui->all_rect.third_button);
	free_str(str);
	option_tab_cont(win, gui);
}

void			gui_tab_bar(t_window *win, t_gui *gui)
{
	SDL_SetRenderDrawColor(win->renderer, gui->colors.border_color.r,
						gui->colors.border_color.g, gui->colors.border_color.b,
						gui->colors.border_color.a);
	SDL_RenderDrawLine(win->renderer, gui->all_rect.tab_camera_button.x,
		gui->all_rect.tab_options_button.y + gui->all_rect.tab_options_button.h,
		gui->all_rect.tab_camera_button.x + gui->all_rect.tab_options_button.x +
		gui->all_rect.tab_options_button.w, gui->all_rect.tab_options_button.y +
		gui->all_rect.tab_options_button.h);
	if (g_camera_tab_pressed == 1)
		camera_tab(win, gui);
	else
		render_tab_bar(win, &gui->colors.border_color,
						&gui->all_rect.tab_camera_button, "Camera");
	if (g_objects_tab_pressed == 1)
		objects_tab(win, gui);
	else
		render_tab_bar(win, &gui->colors.border_color,
						&gui->all_rect.tab_objects_button, "Objects");
	if (g_options_tab_pressed == 1)
		option_tab(win, gui);
	else
		render_tab_bar(win, &gui->colors.border_color,
						&gui->all_rect.tab_options_button, "Options");
}
