/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:54:26 by alex              #+#    #+#             */
/*   Updated: 2020/12/29 16:23:03 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt.h"

void			draw_text(t_window *win, SDL_Rect *rect,
					char *str, t_colors *color)
{
	SDL_Texture	*text;
	SDL_Rect	ptr;
	int			w;
	int			h;

	g_font_size = FONT_TEXT;
	text = render_text(str, "font/Title.ttf", color->text_color, win->renderer);
	SDL_QueryTexture(text, NULL, NULL, &w, &h);
	ptr.x = rect->x + MARGIN;
	ptr.y = rect->y + rect->h / 2 - h / 2;
	ptr.w = w;
	ptr.h = h;
	render_rect(text, win->renderer, &ptr);
}

char			*itoa_float(float num)
{
	char		*str1;
	char		*str2;
	char		*tmp;
	int			ptr;
	int			aftd;

	ptr = (int)num;
	aftd = ((int)num - ptr) * 10;
	if (aftd < 0)
		aftd = aftd * -1;
	str1 = ft_itoa(ptr);
	str2 = ft_itoa(aftd);
	tmp = ft_strjoin(str1, ".");
	free(str1);
	str1 = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (str1);
}

void			draw_title_ray_tracing(t_window *win, SDL_Color *color)
{
	SDL_Texture	*rt_text;
	SDL_Rect	rect;
	int			w;
	int			h;

	g_font_size = FONT_TITLE_SIZE * 2;
	rt_text = render_text("Ray Tracing", "font/Title_font_CAT.ttf",
							*color, win->renderer);
	SDL_QueryTexture(rt_text, NULL, NULL, &w, &h);
	if (win->width / 4 >= w)
	{
		rect.x = (win->width - win->width / 4) + (win->width / 4 - w) / 2;
		rect.y = MARGIN_Y;
		rect.w = w;
		rect.h = h;
	}
	else
	{
		rect.x = (win->width - win->width / 4) + MARGIN;
		rect.y = MARGIN_Y;
		rect.w = win->width / 4 - MARGIN * 2;
		rect.h = h;
	}
	render_rect(rt_text, win->renderer, &rect);
	SDL_DestroyTexture(rt_text);
}

void			free_str(char *str[4])
{
	int i;

	i = 0;
	while (i <= 3)
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
}

void			gui_disk_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	get_float_data(gui->current_instance.r, "Radius", str);
	draw_button(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
}
