/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:33:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 16:26:25 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "window.h"

static void	init_rect_tree(t_all_rect *rect, t_window *win)
{
	rect->third_button = init_rect_size(win->width - win->width / 4 +
		SPACER, rect->second_button.y + rect->second_button.h +
		MARGIN_Y * 4, win->width / 4, 30);
	rect->fourth_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->third_button.y + rect->third_button.h +
		MARGIN_Y * 4, win->width / 4, 30);
	rect->fifth_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->fourth_button.y + rect->fourth_button.h + MARGIN_Y * 4,
		win->width / 4, 30);
	rect->sixth_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->fifth_button.y + rect->fifth_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->seven_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->sixth_button.y + rect->sixth_button.h + MARGIN_Y * 4,
		win->width / 4, 30);
	rect->eight_button = init_rect_size(win->width - win->width / 4 +
	SPACER, rect->seven_button.y + rect->seven_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
}

static void	init_rect_two(t_all_rect *rect, t_window *win)
{
	rect->nine_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->eight_button.y + rect->eight_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->ten_button = init_rect_size(win->width - win->width / 4 +
	SPACER, rect->nine_button.y + rect->nine_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->eleven_button = init_rect_size(win->width - win->width / 4 +
	SPACER, rect->ten_button.y + rect->ten_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->twelve_button = init_rect_size(win->width - win->width / 4 +
	SPACER, rect->eleven_button.y + rect->eleven_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->thirteen_button = init_rect_size(win->width - win->width / 4 +
	SPACER, rect->twelve_button.y + rect->twelve_button.h + MARGIN_Y * 2,
		win->width / 4, 30);
	rect->save_img_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->third_button.y + rect->third_button.h + MARGIN_Y * 4,
		win->width / 4, 30);
}

void		init_rect(t_all_rect *rect, t_window *win)
{
	rect->background = init_rect_size(win->width - win->width / 4,
		0, win->width / 4, win->height);
	rect->title_button = init_rect_size(win->width - win->width / 4,
		MARGIN_Y, win->width / 4, MARGIN_Y * 3);
	rect->tab_camera_button = init_rect_size(win->width - win->width / 4,
		win->height / 13, (win->width / 4) / 3, 30);
	rect->tab_objects_button = init_rect_size(win->width - win->width / 4
		+ rect->tab_camera_button.w,
		win->height / 13, (win->width / 4) / 3, 30);
	rect->tab_options_button = init_rect_size(win->width - win->width / 4 +
		rect->tab_camera_button.w + rect->tab_objects_button.w,
		win->height / 13, (win->width / 4) / 3, 30);
	rect->first_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->tab_camera_button.y + rect->tab_camera_button.h + MARGIN_Y,
		win->width / 4, 30);
	rect->second_button = init_rect_size(win->width - win->width / 4 + SPACER,
		rect->first_button.y + rect->first_button.h + MARGIN_Y,
		win->width / 4, 30);
	init_rect_tree(rect, win);
	init_rect_two(rect, win);
}

void		init_colors(t_colors *color)
{
	color->background_color = init_color(0, 0, 0, 0);
	color->border_color = init_color(43, 43, 45, 0);
	color->inside_color = init_color(28, 28, 30, 0);
	color->text_color = init_color(255, 255, 255, 0);
}

void		init_gui(t_gui *const gui, t_window win)
{
	init_colors(&gui->colors);
	init_rect(&gui->all_rect, &win);
}
