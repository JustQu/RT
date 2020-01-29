/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:18:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/01/28 17:59:32 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdint.h>

#include "SDL.h"
#include <OpenCL/opencl.h>

#include "rt.h"
#include "libft.h"

typedef struct	s_clp
{
	cl_platform_id		pl_id;
	cl_device_id		de_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	queue;
}				t_clp;

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

size_t read_kernel(char *file_name, char **str)
{
	int		fd;
	char	*tmp;
	int		ret;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return 0;
	*str = ft_strdup("");
	ret = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		tmp = *str;
		*str = ft_strjoin(*str, buff);
		ft_strdel(&tmp);
	}
	if (ret < 0)
	{
		ft_strdel(str);
		return 0;
	}
	close(fd);
	return (size_t)ft_strlen(*str);
}

void gradient(t_clp *clp, uint32_t *image)
{
	char *source_str;
	size_t source_size = read_kernel("beatifull_fradient.cl", &source_str);
	cl_mem buffer = clCreateBuffer(clp->context, CL_MEM_WRITE_ONLY, sizeof(uint32_t) * 1920 * 1080, NULL, &clp->ret);

	cl_program program = clCreateProgramWithSource(clp->context, 1, &source_str, &source_size, &clp->ret);
	clBuildProgram(program, 1, &clp->de_id, NULL, NULL);
	
}

int main(int ac, char **av)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
	uint32_t *image = (uint32_t *)malloc(sizeof(uint32_t) * 1920 * 1080);
	memset(image, 55, sizeof(uint32_t) * 1920 * 1080);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, 1920, 1080);
	t_bool quit = 0;
	t_clp *clp = initOpenCl();
	gradient(clp, image);
	SDL_UpdateTexture(texture, NULL, image, sizeof(uint32_t) * 1920);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	while (!quit)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
	}

	SDL_Quit();
}