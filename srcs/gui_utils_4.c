/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:02:53 by alex              #+#    #+#             */
/*   Updated: 2020/12/29 18:41:21 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			draw_for_button(t_window *win, SDL_Rect *rect, t_colors *color)
{
	SDL_SetRenderDrawColor(win->renderer, color->inside_color.r,
		color->inside_color.g, color->inside_color.b, color->inside_color.a);
	SDL_RenderFillRect(win->renderer, rect);
	SDL_SetRenderDrawColor(win->renderer, color->border_color.r,
		color->border_color.g, color->border_color.b, color->border_color.a);
	SDL_RenderDrawRect(win->renderer, rect);
}

void			gui_init_title(t_window *win,
					t_all_rect *all_rect, t_colors *color)
{
	if (win == NULL || all_rect == NULL || color == NULL)
		return ;
	if (TTF_Init() == -1)
		return ;
	if (win->height >= 300 && win->width >= 200)
		draw_title_ray_tracing(win, &color->text_color);
}

void			gui_triangle_vision(t_window *win, t_gui *gui)
{
	char		*str[4];

	if (gui->options.depth >= 0)
		;
	get_float4_data(gui->current_instance.v1, "Vertex 1", str);
	draw_button_xyz(win, &gui->all_rect.fifth_button, str, &gui->colors);
	free_str(str);
	get_float4_data(gui->current_instance.v2, "Vertex 2", str);
	draw_button_xyz(win, &gui->all_rect.sixth_button, str, &gui->colors);
	free_str(str);
}

void			get_texture_data_2(int ptr, char **str)
{
	if (ptr == 6)
		str[1] = ft_strdup("smooth_perlin");
	else if (ptr == 7)
		str[1] = ft_strdup("turbulence_perlin");
	else if (ptr == 8)
		str[1] = ft_strdup("wave_perlin");
	else if (ptr == 9)
		str[1] = ft_strdup("image");
	else if (ptr < 0 || ptr > 9)
		str[1] = ft_strdup("no texture");
}
