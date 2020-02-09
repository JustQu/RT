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

#include <time.h> //for primitive fps count

FILE *f;
int fd;
#define DEBUG

#ifdef DEBUG
# include <assert.h>
#endif

#ifdef __APPLE__
# include "OpenCL/opencl.h"
#elif _WIN64
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
size_t	read_kernel(char *file_name, char **str)
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



void	display_image(t_window *w)
{
	// static SDL_Window 	*window = NULL;
	// static SDL_Renderer	*renderer = NULL;
	// static SDL_Texture	*texture = NULL;

	SDL_UpdateTexture(w->texture, NULL, w->image, sizeof(uint32_t) * w->width);
	SDL_RenderClear(w->renderer);
	SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
	SDL_RenderPresent(w->renderer);
}

int		catch_event()
{
	SDL_Event event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			return 1;
		}
		if (event.type = SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_MOVED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;
				case SDL_WINDOWEVENT_CLOSE:
					return 1;

				case SDL_WINDOWEVENT_RESIZED:
				{
					fprintf(f, "Window size changed to %dx%d\n",
							event.window.data1, event.window.data2);
				} break;

			}
		}
		if (event.type == SDL_KEYDOWN)
		{

		}
		if (event.type == SDL_KEYUP)
		{

		}
		if (event.type = SDL_MOUSEBUTTONDOWN)
		{

		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{

		}
		//check input
		//switch kernel here?
	}
	return 0;
}

void cl_error(t_cl_program *program, t_clp *clp, int code)
{
	if (code != CL_SUCCESS)
	{
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG, 0,
							  NULL, &log_size);
		// Allocate memory for the log
		char *log = (char *)malloc(log_size);
		// Get the log
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG,
							  log_size, log, NULL);
		// Print the log
		printf("\n\n\n\n\n%s\n", log);
		fprintf(f, "\n\n\n\n\n%s\n", log);
	}
}

//use work_size later, when inits will be splitted
void	create_render_program(t_cl_program *program, t_clp *clp,
	int work_size)
{
	program->input = clCreateBuffer(clp->context, CL_MEM_READ_ONLY,
		sizeof(uint32_t) * program->work_size, NULL, &clp->ret);
	cl_error(program, clp, clp->ret);
	assert(!clp->ret);
	program->output = clCreateBuffer(clp->context, CL_MEM_WRITE_ONLY,
		sizeof(uint32_t) * program->work_size, NULL, &clp->ret);
	cl_error(program, clp, clp->ret);
	assert(!clp->ret);
	program->program = clCreateProgramWithSource(clp->context, 1,
		&program->source_str, NULL, &clp->ret);
	cl_error(program, clp, clp->ret);
	assert(!clp->ret);
	clBuildProgram(program->program, 1, &clp->de_id, "-cl-opt-disable", NULL, NULL);
	program->kernel = clCreateKernel(program->program,"render2", &clp->ret);
	cl_error(program, clp, clp->ret);
	assert(!clp->ret);

}

void	fps_count()
{
	static clock_t	end = 0;
	static int		count = 0;
	static clock_t	start = 0;
	int				secs;

	end = clock();
	count++;
	secs = (float)(end - start)/ CLK_TCK;
	if (secs > 2)
	{
		fprintf(f, "FPS: %f\n", count / 2.0f);
		start = clock();
		end = 0;
		count = 0;
	}
}

//NOTE: test case. Delete later
#include "stdlib.h"
struct s_sphere
{
	cl_float4	origin;
	cl_float	radius;
	uint32_t	color;
};

typedef struct s_sphere t_sphere;

t_sphere	*generate_spheres(int number)
{
	t_sphere	*spheres;

	spheres = malloc(sizeof(t_sphere) * number);
	srand(2);
	for (int i = 0; i < number; i++)
	{
		spheres[i].origin.x = -200 + rand() % 1201;
		spheres[i].origin.y = -60 + rand() % 761;
		spheres[i].origin.z = 50 + rand() % 20;
		spheres[i].origin.w = 0;
		// spheres[i].origin.x = 400;
		// spheres[i].origin.y = 320;
		// spheres[i].origin.z = 100;
		// spheres[i].origin.w = 0;
		spheres[i].radius = 100;
		// spheres[i].color = 0x00ff0000;
		spheres[i].color = (64 + rand() % 196) << 16 |
							(64 + rand() % 196) << 8 |
							0;
	printf("generated: %d: (%f,%f,%f) %f %X\n", i, spheres[i].origin.x, spheres[i].origin.y,
			spheres[i].origin.z, spheres[i].radius, spheres[i].color);
	}
	return spheres;
}
///////////////

// init scene
int		read_data(t_scene *scene)
{

}
int		init_win(t_window *window);
int		init_cl(t_clp *clp);
int		init_renderer(t_cl_program *cl_program);
/**
** @brief
** default initialization
** @param window
** @param cl_program
** @return ** int
*/
int		init(t_window *window, t_cl_program *cl_program, t_scene *scene)
{
	read_data(scene);
	return 0;
}

#include "windows.h"
//NOTE: можно все структуры в одну структуру запихнуть
//	можно просто сделать перменные в функции
void	render_loop(t_program *p)
{
	t_window		window;
	t_cl_program	program;
	t_scene			scene;
	t_bool			quit;
	// t_cl_program	program;

	quit = FALSE;
	//init first data
	//init window
	//init opecl
	//init renderer
	t_sphere *m = generate_spheres(10);
	printf("space between %s and %s: %ld\n", "g", "h", (long)(&m[0]) - (long)(&m[1]));
	cl_mem spheres = clCreateBuffer(p->clp.context, CL_MEM_READ_WRITE |
		 CL_MEM_COPY_HOST_PTR, sizeof(t_sphere) * 10, m, &p->clp.ret);
	assert(!p->clp.ret);

	create_render_program(&p->program, &p->clp, -1);
	clSetKernelArg(p->program.kernel, 0, sizeof(cl_mem),
				   (void *)&p->program.output);
	clSetKernelArg(p->program.kernel, 1, sizeof(cl_mem), &spheres);
	// clSetKernelArg(p->program.kernel, 2, sizeof(cl_mem), &rays);
	clEnqueueNDRangeKernel(p->clp.queue, p->program.kernel, 1, NULL,
						   &p->program.work_size, &p->program.work_group_size, 0, NULL, NULL);
	clEnqueueReadBuffer(p->clp.queue, p->program.output, CL_TRUE, 0,
						p->program.work_size * sizeof(uint32_t), p->window.image, 0, NULL, NULL);
	while (!quit)
	{
		if (catch_event() == 1)
			quit = TRUE;
		display_image(&p->window);
		fps_count();
	}
}

/**
** @brief
** initializing main part of the program
** there are mostly only constants and malloc
** @param program
** get address of t_program struct and store info in it
** @return ** int
*/
int init_program(t_program *program)
{
	t_program	p;
	t_window	*w;

	fprintf(f, "hello\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	w = &p.window;
	w->width = 800;
	w->height = 640;
	p.program.work_group_size = 64;
	p.program.work_size = w->width * w->height;
	read_kernel("../beautiful_gradient.cl", &p.program.source_str);
	w->image = (uint32_t *)malloc(sizeof(uint32_t) * p.program.work_size);
	memset(w->image, 64, sizeof(uint32_t) * p.program.work_size);
	w->ptr = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w->width, w->height, SDL_WINDOW_RESIZABLE);
	assert(w->ptr);
	w->renderer = SDL_CreateRenderer(w->ptr, -1, SDL_RENDERER_ACCELERATED);
	assert(w->renderer);
	w->texture = SDL_CreateTexture(w->renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, w->width, w->height);
	assert(w->texture);
	p.clp = init_opencl();
	*program = p;
	fprintf(f, "program inited\n");
}

#if 0
#include "windows.h"
int WinMain(HINSTANCE hInstance,
  			HINSTANCE hPrevInstance,
  			LPSTR     lpCmdLine,
  			int       nShowCmd)
#else
#include "conio.h"
int main(int argc, char *argv[])
#endif
{
	t_program	params;
	4;
	printf("ololo\n");
	f = fopen("out", "w");
	fprintf(f, "start\n");
	//read data
	init_program(&params);
	render_loop(&params);
	SDL_Quit();
	getch();
	return (0);
}
