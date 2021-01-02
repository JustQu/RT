/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:49:42 by alex              #+#    #+#             */
/*   Updated: 2020/12/21 13:25:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void			draw_line(t_window *win, t_colors *color,
					SDL_Rect rect, SDL_Rect rect_2)
{
	SDL_SetRenderDrawColor(win->renderer, color->text_color.r,
			color->text_color.g, color->text_color.b, color->text_color.a);
	SDL_RenderDrawLine(win->renderer, rect.x, rect_2.y - 10,
						rect_2.x + rect_2.w, rect_2.y - 10);
}

void			minimum_rect_size(int w, int h, SDL_Rect *rect, SDL_Rect *ptr)
{
	if (w <= rect->w)
	{
		ptr->x = rect->x + rect->w / 2 - w / 2;
		ptr->y = rect->y + rect->h / 2 - h / 2;
		ptr->w = w;
		ptr->h = h;
	}
	else
	{
		ptr->x = rect->x + 1;
		ptr->y = rect->y;
		ptr->w = rect->w - 2;
		ptr->h = rect->h / 2 + h;
	}
}

void			type_ambien_il(t_window *win,
					t_gui *gui)
{
	char *str[4];

	if (gui->current_light.type == 0)
	{
		get_float_data(1, "coefficient", str);
		draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
		free_str(str);
	}
	if (gui->current_light.type == 1)
	{
		get_float_data(1, "min_amount", str);
		draw_button(win, &gui->all_rect.sixth_button, str, &gui->colors);
		free_str(str);
	}
}

SDL_Texture		*create_tab_subtitles(t_window *win, char *str,
					SDL_Color *color)
{
	SDL_Texture	*text;

	g_font_size = FONT_SUBTITLE_SIZE;
	text = render_text(str, "font/Title.ttf", *color, win->renderer);
	return (text);
}

void			draw_button_rect_xyz(t_window *win, SDL_Rect *rect,
				char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
		color->inside_color.g, color->inside_color.b, color->inside_color.a);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, rect);
	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf", color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr.x = rect->x + rect->w / 2 - w / 4;
	ptr.y = rect->y + rect->h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}
