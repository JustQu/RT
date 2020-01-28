/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/01/28 17:23:58 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdint.h>

#include "SDL.h"

#include "rt.h"

int main(int ac, char **av)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	printf("1");
	SDL_Window *window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	printf("2");
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
	uint32_t *image = (uint32_t *)malloc(sizeof(uint32_t) * 800 * 800);
	memset(image, 55, sizeof(uint32_t) * 800 * 800);
	printf("3");
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, 800, 800);
	t_bool quit = 0;
	printf("4");

	SDL_UpdateTexture(texture, NULL, image, sizeof(uint32_t) * 800);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	while (!quit)
	{
	printf("5");

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
	}

	printf("6");

	SDL_Quit();
}