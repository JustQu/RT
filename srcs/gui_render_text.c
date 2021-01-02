/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_render_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:21:17 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 02:57:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

SDL_Texture			*render_text(char *message, char *font_file,
		SDL_Color color, SDL_Renderer *renderer)
{
	TTF_Font		*font;
	SDL_Surface		*surf;
	SDL_Texture		*texture;

	if (!message)
		return (NULL);
	font = TTF_OpenFont(font_file, g_font_size);
	if (font == NULL)
		return (NULL);
	surf = TTF_RenderText_Blended(font, message, color);
	if (surf == NULL)
		return (NULL);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
		return (NULL);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return (texture);
}
