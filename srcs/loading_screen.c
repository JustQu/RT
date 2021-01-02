/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 23:23:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:54:38 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

static char		*g_load_arr[20] = {
	"./load/0001.png", "./load/0002.png", "./load/0003.png", "./load/0004.png",
	"./load/0005.png", "./load/0006.png", "./load/0007.png", "./load/0008.png",
	"./load/0009.png", "./load/0010.png", "./load/0011.png", "./load/0012.png",
	"./load/0013.png", "./load/0014.png", "./load/0015.png", "./load/0016.png",
	"./load/0017.png", "./load/0018.png", "./load/0019.png", "./load/0020.png"
};

static char		*g_text_arr[32] = {
	"./load_text/1001.png", "./load_text/1002.png", "./load_text/1003.png",
	"./load_text/1004.png", "./load_text/1005.png", "./load_text/1006.png",
	"./load_text/1007.png", "./load_text/1008.png", "./load_text/1009.png",
	"./load_text/1010.png", "./load_text/1011.png", "./load_text/1012.png",
	"./load_text/1013.png", "./load_text/1014.png", "./load_text/1015.png",
	"./load_text/1016.png", "./load_text/1017.png", "./load_text/1018.png",
	"./load_text/1019.png", "./load_text/1020.png", "./load_text/1021.png",
	"./load_text/1022.png", "./load_text/1023.png", "./load_text/1024.png",
	"./load_text/1025.png", "./load_text/1026.png", "./load_text/1027.png",
	"./load_text/1028.png", "./load_text/1029.png", "./load_text/1030.png",
	"./load_text/1031.png", "./load_text/1032.png"
};

static int g_state = 0;

void			resize_imgs(t_window *window, SDL_Event e, SDL_Rect *rect,
							SDL_Rect *mes_rec)
{
	window->width = e.window.data1;
	window->height = e.window.data2;
	*rect = (SDL_Rect){window->width / 2 - 500 * window->height / 658 / 2,
						0,
						500 * window->height / 658,
						658 * window->height / 658};
	*mes_rec = (SDL_Rect){0, 0,
						800 * window->width / 800 / 5,
						600 * window->width / 800 / 5};
}

void			add_img_to_screen(t_window *window, SDL_Surface *sur,
								SDL_Rect rect)
{
	SDL_Texture	*tex;

	tex = SDL_CreateTextureFromSurface(window->renderer, sur);
	SDL_RenderCopy(window->renderer, tex, NULL, &rect);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(tex);
	SDL_Delay(25);
}

void			loading_cycle(t_window *window, SDL_Rect rect, SDL_Rect mes_rec)
{
	int			i;
	int			j;
	SDL_Surface *sur;
	SDL_Event	e;

	i = 0;
	j = 0;
	while (g_state != 1)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				SDL_Quit();
			if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				resize_imgs(window, e, &rect, &mes_rec);
		}
		SDL_RenderFillRect(window->renderer, NULL);
		sur = IMG_Load(g_load_arr[j]);
		add_img_to_screen(window, sur, rect);
		sur = IMG_Load(g_text_arr[i]);
		add_img_to_screen(window, sur, mes_rec);
		SDL_RenderPresent(window->renderer);
		i = i == 31 ? 0 : i + 1;
		j = j == 19 ? 0 : j + 1;
	}
}

int				test_thread(void *ptr)
{
	int				r;
	t_cl_program	*p;

	p = ptr;
	SDL_Delay(3000);
	r = clBuildProgram(p->program, 1, &p->info.de_id,
						"-cl-std=CL2.0", NULL, NULL);
	g_state = 1;
	return (r);
}

void			loading_screen(t_cl_program *p, t_window *window)
{
	SDL_Thread	*thread;
	int			ret;
	SDL_Rect	mes_rec;
	SDL_Rect	rect;

	mes_rec = (SDL_Rect){0, 0, 800 * window->width / 800 / 5,
						600 * window->width / 800 / 5};
	rect = (SDL_Rect){window->width / 2 - 500 * window->height / 658 / 2,
					0,
					500 * window->height / 658,
					658 * window->height / 658};
	thread = SDL_CreateThread(test_thread, "TestThread", (void *)p);
	SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 0);
	if (NULL == thread)
	{
		ft_putstr_fd("SDL_CreateThread failed: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
	}
	else
	{
		loading_cycle(window, rect, mes_rec);
		SDL_WaitThread(thread, &ret);
	}
}
