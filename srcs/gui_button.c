/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:52:14 by alex              #+#    #+#             */
/*   Updated: 2020/12/21 13:39:06 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"
#include "rt_error.h"

void			draw_button_rect(t_window *win, SDL_Rect *rect,
				char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	draw_for_button(win, rect, color);
	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf", color->text_color, win->renderer);
	if (!text)
	{
		rt_warning("Warning! Could not render text");
		return ;
	}
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	while (w >= rect->w)
	{
		g_font_size -= 1;
		text = render_text(str, "font/Title.ttf", color->text_color,
						win->renderer);
		SDL_QueryTexture(text, NULL, NULL, &w, &h);
	}
	minimum_rect_size(w, h, rect, &ptr);
	render_rect(text, win->renderer, &ptr);
}

SDL_Texture		*draw_button_rgb_l(t_window *win, char **str_xyz,
					t_colors *color)
{
	SDL_Texture *text;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str_xyz[0], "font/Title.ttf", color->text_color,
						win->renderer);
	return (text);
}

void			draw_button_rgb(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	text = draw_button_rgb_l(win, str_xyz, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr = init_rect_size(win->width - win->width / 4 + MARGIN, rect->y, w, h);
	render_rect(text, win->renderer, &ptr);
	button = init_rect_size(win->width - win->width / 4 + MARGIN, rect->y + h,
							(rect->w - MARGIN * 2) / 3, rect->h);
	draw_button_rect_xyz(win, &button, str_xyz[1], color);
	draw_text(win, &button, "r :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[2], color);
	draw_text(win, &button, "g :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[3], color);
	draw_text(win, &button, "b :", color);
}

void			draw_button_xyz(t_window *win, SDL_Rect *rect,
					char **str_xyz, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	text = draw_button_rgb_l(win, str_xyz, color);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y, w, h);
	render_rect(text, win->renderer, &ptr);
	button = init_rect_size(win->width - win->width / 4 + MARGIN,
		rect->y + h, (rect->w - MARGIN * 2) / 3, rect->h);
	draw_button_rect_xyz(win, &button, str_xyz[1], color);
	draw_text(win, &button, "x :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 4) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[2], color);
	draw_text(win, &button, "y :", color);
	button.x += button.w + MARGIN;
	button.w = (rect->w - MARGIN * 6) / 3;
	draw_button_rect_xyz(win, &button, str_xyz[3], color);
	draw_text(win, &button, "z :", color);
}

void			draw_button(t_window *win, SDL_Rect *rect,
					char **str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	button;
	SDL_Rect	ptr;
	int			w;
	int			h;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str[0], "font/Title.ttf", color->text_color,
						win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr = init_rect_size(win->width - win->width / 4 + MARGIN, rect->y, w, h);
	render_rect(text, win->renderer, &ptr);
	SDL_DestroyTexture(text);
	if (w <= win->width && str[1] != NULL)
	{
		button = init_rect_size(rect->x + MARGIN, rect->y,
			rect->w - MARGIN * 2 - 150, rect->h);
		draw_button_rect(win, &button, str[1], color);
	}
}
