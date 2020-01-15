/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:27:45 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 19:11:04 by dwalda-r         ###   ########.fr       */
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

void gpurender(t_param *p)
{
	char		*source;
	size_t		len;
	cl_program	pr;
	cl_kernel	kernel;
	cl_mem		img;

	len = read_kernel("uvmap.cl", &source);
	img = clCreateBuffer(p->clprm->context, CL_MEM_WRITE_ONLY,
	SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(cl_float3), NULL, &(p->clprm->ret));
	pr = clCreateProgramWithSource(p->clprm->context, 1,
	(const char **)&source, (const size_t *)&len, &(p->clprm->ret));
	p->clprm->ret = clBuildProgram(pr, 1, &(p->clprm->de_id), NULL, NULL, NULL);
	kernel = clCreateKernel(pr, "uvmap", &(p->clprm->ret));
	p->clprm->ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&img);
	size_t global_item_size = GLOBAL_SIZE;
	size_t local_item_size = LOCAL_SIZE;
	p->clprm->ret = clEnqueueNDRangeKernel(p->clprm->queue, kernel, 1, NULL,
	&global_item_size, &local_item_size, 0, NULL, NULL);
	cl_float3 *popka = (cl_float3 *)malloc(sizeof(cl_float3) * SCREEN_WIDTH * SCREEN_HEIGHT);
	p->clprm->ret = clEnqueueReadBuffer(p->clprm->queue, img, CL_TRUE, 0,
	SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(cl_float3), popka, 0, NULL, NULL);
	for (int j = 0; j < SCREEN_HEIGHT; j++)
	{
		for (int i = 0; i < SCREEN_WIDTH; i++)
		{
			int color = (int)(popka[j * SCREEN_WIDTH + i]).s[0] << 16 | (int)(popka[j * SCREEN_WIDTH + i]).s[1] << 8 | (int)(popka[j * SCREEN_WIDTH + i]).s[2];
			printf("%f, %f, %f\n", popka[j * SCREEN_WIDTH + i].s[0], popka[j * SCREEN_WIDTH + i].s[1], popka[j * SCREEN_WIDTH + i].s[2]);
			p->img[j * SCREEN_WIDTH + i] = color;
		}
	}
}

void rtCycle(t_param *p)
{
	SDL_Event	e;
	t_bool quit;
	SDL_Texture	*tex;

	tex = SDL_CreateTexture(p->windata.ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	quit = FALSE;
	// render(p);
	gpurender(p);
	SDL_UpdateTexture(tex, NULL, p->img, sizeof(Uint32) * SCREEN_WIDTH);
	SDL_RenderClear(p->windata.ren);
	SDL_RenderCopy(p->windata.ren, tex, NULL, NULL);
	SDL_RenderPresent(p->windata.ren);
	while (!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}
}

t_clp	*initOpenCl()
{
	t_clp	*clp;

	clp = (t_clp *)malloc(sizeof(t_clp));
	clp->pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), &(clp->ret_num_platforms));
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_GPU, 1, &(clp->de_id),
	&(clp->ret_num_devices));
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL, &(clp->ret));
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	return clp;
}

void	initParam(t_param *p)
{
	p->world.nobjs = 0;
	p->world.nlights = 0;
	p->windata.win = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	p->windata.ren = SDL_CreateRenderer(p->windata.win, -1, SDL_RENDERER_ACCELERATED);
	p->img = (Uint32 *)malloc(sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
	ft_memset(p->img, 55, sizeof(Uint32) * SCREEN_WIDTH * SCREEN_HEIGHT);
	p->clprm = initOpenCl();
}

int		catch_errors(t_param *p, char **arg, int ac)
{
	int fd;

	fd = open(arg[1], O_RDONLY);
	if (ac != 2)
	{
		ft_putendl_fd("usage: ./RTv1 file_name", 1);
		return (0);
	}
	if (fd < 0)
	{
		ft_putendl_fd("error: file does not exist", 2);
		return (0);
	}
	if (!read_all(fd, p))
	{
		ft_putendl_fd("error: bad data", 2);
		return (0);
	}
	return (1);
}



int main(int ac, char **arg)
{
	t_param p;
	SDL_Init(SDL_INIT_EVERYTHING);
	initParam(&p);
	if (!catch_errors(&p, arg, ac))
		return (1);
	world_to_camera(&p);
	rotate_camera(&p);
	rtCycle(&p);
	SDL_Quit();
}