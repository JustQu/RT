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
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>

FILE *f;
#define DEBUG


#ifdef DEBUG
# include <assert.h>
#endif

#ifdef __APPLE__
# include "OpenCL/opencl.h"
#elif _WIN64
# include "windows.h"
# include "CL/cl.h"
#endif

#include "SDL.h"

#include "rt.h"
#include "libft.h"

/**
** @brief
** L1 Cache = Local Memory(OpenCL) = Shared Memory(CUDA)
*/

/**
** @brief
** информация о opencl
*/
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

/**
** @brief
** top level struct of the program
** that info and contains other structs
*/
struct	s_program
{
	int				width; // window width
	int				height; // window heigh
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	uint32_t		*image; //image to render and display
	SDL_Texture		*texture; //texture to display image on winow
	t_clp			clp; //opencl common info
	size_t			global_item_size;
	size_t			local_item_size;
	char			*source_str; // думаю надо будет как-то вынести
	uint32_t		source_size;
} s_program_default = {.width = 800, .height = 640};

typedef struct s_program	t_program;

/**
** @todo
** error check
** @brief
** init t_clp structwith opencl info
** @return ** t_clp
*/
t_clp	init_opencl()
{
	t_clp	clp;

	//clp = (t_clp *)malloc(sizeof(t_clp));
	clp.pl_id = NULL;
	clp.de_id = NULL;
	clp.ret = clGetPlatformIDs(1, &(clp.pl_id), &(clp.ret_num_platforms));
	if (clp.ret != CL_SUCCESS)
		fprintf(f, "%s\n", "clGetPlatformIDs error");

	clp.ret = clGetDeviceIDs(clp.pl_id, CL_DEVICE_TYPE_GPU, 1, &(clp.de_id),
		&(clp.ret_num_devices));
	if (clp.ret != CL_SUCCESS)
		fprintf(f, "%s\n", "clGetDeviceIDs error");

	clp.context = clCreateContext(NULL, 1, &(clp.de_id), NULL, NULL,
		&(clp.ret));
	if (clp.ret != CL_SUCCESS)
		fprintf(f, "%s\n", "clCreateContext error");

	clp.queue = clCreateCommandQueue(clp.context, clp.de_id, 0, &(clp.ret));
	if (clp.ret != CL_SUCCESS)
		fprintf(f, "%s\n", "clCreateCommandQueue error");

	return clp;
}

/**
** @brief
** считывание opencl кода из файла file_name в строку str
** @param file_name
** @param str
** @return ** size_t
*/
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

/**
** @brief
** output image in window
** @param p
** @return ** void
*/
/* void show_image(t_program *p)
{
	static SDL_Window	*window = NULL;
	static SDL_Renderer	*renderer = NULL;

	if (!window)
		window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, p.height, p.widht, NULL);
} */

struct s_cl_program
{
	cl_program	program;
	cl_kernel	kernel;
	cl_mem		input;
	cl_mem		output;
};
typedef struct s_cl_program	t_cl_program;

void render_loop(t_program *p)
{
	t_bool		quit;
	SDL_Event	event;
	cl_kernel	kernel;
	cl_mem		buffer;

	quit = FALSE;
	//kernel = clCreateKernel();
	//create kernel
	while (!quit)
	{
		if (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
			//check input
			//switch kernel here?
		}
		//render image
		//show rendered image
	}
}

/**
** @brief
** initializing main part of the program
** @param program
** get address of t_program struct and store info in it
** @return ** int
*/
int init_program(t_program *program)
{
	t_program	p;

	SDL_Init(SDL_INIT_EVERYTHING);
	p = s_program_default;
	fprintf(f, "%d %d\n", p.width, p.height);
	//create sdl window first
	p.window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		 p.width, p.height, 0);
	if (!p.window)
		return -1;
#ifdef DEBUG
	assert(p.window);
#endif
	//create renderer using sdl window
	p.renderer = SDL_CreateRenderer(p.window, -1, SDL_RENDERER_ACCELERATED);
#ifdef DEBUG
	assert(p.renderer);
#endif
	//create image
	p.image = (uint32_t *)malloc(sizeof(uint32_t) * p.width * p.height);
#ifdef DEBUG
	assert(p.image);
#endif
	//set image pixel values to 0
	memset(p.image, 64, sizeof(uint32_t) * p.width * p.height);
	//create texture to display image in window
	p.texture = SDL_CreateTexture(p.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, p.width, p.height);
#ifdef DEBUG
	assert(p.texture);
#endif
	//init opencl
	p.clp = init_opencl();
	p.source_size = read_kernel("../beautiful_gradient.cl", &p.source_str);
	fprintf(f, "init source size %d\n", p.source_size);
	p.global_item_size = p.width * p.height;
	p.local_item_size = 64;
	*program = p;
}

#if defined(_WIN64)
int WinMain(HINSTANCE hInstance,
  			HINSTANCE hPrevInstance,
  			LPSTR     lpCmdLine,
  			int       nShowCmd)
#else
int main(int ac, char **av)
#endif
{
	//SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_Window *window = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
	//	SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
	//SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 ,
	//	SDL_RENDERER_ACCELERATED);
	//uint32_t *image = (uint32_t *)malloc(sizeof(uint32_t) * 800 * 640);
	//memset(image, 55, sizeof(uint32_t) * 800 * 640);
	//SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	//	SDL_TEXTUREACCESS_STREAMING, 800, 640);
	//t_clp *clp = init_opencl();

	f = fopen("out", "w");

	t_program	params;
	t_bool		quit;
	char		*source_str;

	init_program(&params);
	uint32_t test = read_kernel("../beautiful_gradient.cl", &source_str);
	fprintf(f, "%d\n", test);
	cl_mem buffer = clCreateBuffer(params.clp.context, CL_MEM_WRITE_ONLY,
		sizeof(uint32_t) * params.width * params.height, NULL, &params.clp.ret);

	cl_program program = clCreateProgramWithSource(params.clp.context, 1,
		&source_str, NULL, &params.clp.ret);
	fprintf(f, "%d\n", params.clp.ret);
	// if (params.clp.ret != CL_SUCCESS)
	// {
	// 	// Determine the size of the log
	// 	size_t log_size;
	// 	clGetProgramBuildInfo(program, params.clp.de_id`,
	// 		 CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

	// 	// Allocate memory for the log
	// 	char *log = (char *)malloc(log_size);

	// 	// Get the log
	// 	clGetProgramBuildInfo(program,  params.clp.de_id,
	// 		CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

	// 	// Print the log
	// 	fprintf(f, "%s\n", log);
	// }
	clBuildProgram(program, 1, &params.clp.de_id, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "render", &params.clp.ret);
	cl_kernel kernel2 = clCreateKernel(program, "render2", &params.clp.ret);
	// if (params.clp.ret != CL_SUCCESS)
	// {
	// 	// Determine the size of the log
	// 	size_t log_size;
	// 	clGetProgramBuildInfo(program, params.clp.de_id,
	// 						  CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

	// 	// Allocate memory for the log
	// 	char *log = (char *)malloc(log_size);

	// 	// Get the log
	// 	clGetProgramBuildInfo(program, params.clp.de_id,
	// 						  CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

	// 	// Print the log
	// 	fprintf(f, "%s\n", log);
	// }

	int offset = 0;
	clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&buffer);
	//запуск ядра
	clEnqueueNDRangeKernel(params.clp.queue, kernel2, 1, NULL,
						   &params.global_item_size, &params.local_item_size, 0, NULL, NULL);
	clEnqueueReadBuffer(params.clp.queue, buffer, CL_TRUE, 0,
						params.global_item_size * sizeof(int), params.image, 0, NULL, NULL);
	SDL_UpdateTexture(params.texture, NULL, params.image,
					  sizeof(uint32_t) * params.width);
	SDL_RenderClear(params.renderer);
	SDL_RenderCopy(params.renderer, params.texture, NULL, NULL);
	SDL_RenderPresent(params.renderer);


	quit = FALSE;
	while (!quit)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
	}

	SDL_Quit();
}
