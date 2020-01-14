/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:27:45 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/14 17:44:20 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(rend, tex, NULL, &pos);
	printf("%d, %d, %d, %d\n", x, y, pos.w, pos.h);
}

t_ray ray_init(t_vec3 origin, t_vec3 dir)
{
	t_ray	r;

	vec4_zero(r.point);
	vec4_zero(r.vec);
	vec3_copy(origin, r.point);
	vec3_copy(dir, r.vec);
	return r;
}

SDL_Texture	*LoadImage(const char* filename, t_windata* windata)
{
	SDL_Surface *loadedImage;
	SDL_Texture *tex;

	loadedImage = NULL;
	tex = NULL;
	loadedImage = SDL_LoadBMP(filename);
	if (loadedImage)
	{
		tex = SDL_CreateTextureFromSurface(windata->ren, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		printf("TEXTURE LOADING ERROR");
	return tex;
}

void		loadpicsAndDraw(t_windata *windata)
{
	SDL_Texture *back;
	SDL_Texture *image;
	int x,y,x1,y1;

	back = LoadImage("./background.bmp", windata);
	image = LoadImage("./image.bmp", windata);
	SDL_RenderClear(windata->ren);
	SDL_QueryTexture(back, NULL, NULL, &x, &y);
	ApplySurface(0,0, back, windata->ren);
	SDL_QueryTexture(image, NULL, NULL, &x1, &y1);
	x1 = SCREEN_WIDTH / 2 - x1 / 2;
	y1 = SCREEN_HEIGHT / 2 - y1 / 2;
	ApplySurface(x1, y1, image, windata->ren);
}


void	point_at(t_ray r, float d, t_vec3 result)
{
	t_vec3	tmp;
	vec3_scale(r.vec, d, tmp);
	vec3_sum(r.point, tmp, result);
}

void	get_color(t_ray r, t_vec3 result)
{
	float	mag;

	vec3_normalize(r.vec);
	mag = 0.5 * (r.vec[oy] + 1);
	result[ox] = (1 - mag) + mag * 0.5;
	result[oy] = (1 - mag) + mag * 0.7;
	result[oz] = (1 - mag) + mag * 1;
	//printf("%f %f %f\n", result[ox], result[oy], result[oz]);
}

SDL_Texture	*gradientTexture(t_windata *windata)
{
	SDL_Texture	*tex;
	Uint32	*pixels;
	t_vec3	color;
	t_vec3	xy;
	t_vec3	uv;
	t_ray	r;

	t_vec3	ll_corner;
	vec3_copy((t_vec3){-2, -1, -1}, ll_corner);
	t_vec3	horizontal;
	vec3_copy((t_vec3){4, 0, 0}, horizontal);
	t_vec3	vertical;
	vec3_copy((t_vec3){0, 2, 0}, vertical);
	t_vec3	origin;
	vec3_zero(origin);

	t_vec3	tmp1;
	t_vec3	tmp2;

	tex = SDL_CreateTexture(windata->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	pixels = (Uint32 *)malloc(sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
	xy[oy] = SCREEN_HEIGHT - 1;
	while(xy[oy] >= 0)
	{
		xy[ox] = 0;
		while (xy[ox] < SCREEN_WIDTH)
		{
			uv[ox] = xy[ox] / SCREEN_WIDTH;
			uv[oy] = 1 - (xy[oy] / SCREEN_HEIGHT);
			vec3_scale(horizontal, uv[ox], tmp1);
			vec3_scale(vertical, uv[oy], tmp2);
			vec3_sum(tmp1, tmp2, tmp1);
			vec3_sum(tmp1, ll_corner, tmp1);
			r = ray_init(origin, tmp1);
			get_color(r, color);
			color[0] = (int)(color[0] * 255) << 16;
			color[1] = (int)(color[1] * 255) << 8;
			color[2] = (int)(color[2] * 255);
			pixels[SCREEN_WIDTH * (int)xy[oy] + (int)xy[ox]] = (int)color[0] | (int)color[1] |
			(int)color[2];
			xy[ox]++;
		}
		xy[oy]--;
	}
	SDL_UpdateTexture(tex, NULL, pixels, sizeof(Uint32) * SCREEN_WIDTH);
	return tex;
}

int main(void)
{
	t_windata windata;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("ERROR");
		return 0;
	}
	windata.win = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (windata.win == NULL)
	{
		printf("ERROR");
		return 0;
	}
	windata.ren = SDL_CreateRenderer(windata.win, -1, SDL_RENDERER_ACCELERATED
	| SDL_RENDERER_PRESENTVSYNC);
	if (windata.ren == NULL)
	{
		printf("ERROR");
		return 0;
	}
	SDL_Texture	*tex;
	tex = gradientTexture(&windata);
	SDL_RenderClear(windata.ren);
	SDL_RenderCopy(windata.ren, tex, NULL, NULL);
	SDL_RenderPresent(windata.ren);
	
	SDL_Event	e;
	int quit = 0;
	while (!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}
	SDL_Quit();
}