/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:27:45 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/16 12:16:37 by dwalda-r         ###   ########.fr       */
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
	
}

void gradient(t_clp *clp, Uint32 *img)
{
	int i = 0;
	char *source_str;
	size_t source_size = read_kernel("render_kernel.cl", &source_str);
	cl_mem c_mem_obj = clCreateBuffer(clp->context, CL_MEM_WRITE_ONLY, GLOBAL_SIZE * sizeof(int), NULL, &clp->ret);
	cl_program program = clCreateProgramWithSource(clp->context, 1, (const char **)&source_str, (const size_t *)&source_size, &clp->ret);
	clp->ret = clBuildProgram(program, 1, &clp->de_id, "-I./includes", NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "render", &clp->ret);
	clp->ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&c_mem_obj);
	size_t global_item_size = GLOBAL_SIZE;
	size_t local_item_size = 64;
	clp->ret = clEnqueueNDRangeKernel(clp->queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	clp->ret = clEnqueueReadBuffer(clp->queue, c_mem_obj, CL_TRUE, 0, GLOBAL_SIZE * sizeof(int), img, 0, NULL, NULL);
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
	// gpurender(p);
	gradient(p->clprm, p->img);
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