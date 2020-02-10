/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/10 18:30:54 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera camera_default = {
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = -1.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.ratio = DEFAULT_WIDTH / DEFAULT_HEIGHT,
	.inv_w = 1 / DEFAULT_WIDTH,
	.inv_h = 1 / DEFAULT_HEIGHT,
	.fov = 90
};


/**
** @TODO: Maybe rewrite?
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

/**
** @brief
** print log about opencl build fail
** @param program
** @param clp
** @param code
** @return ** void
*/
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
		printf("%s\n", log);
	}
}

/**
** @TODO: reading scene from file or default scene
** @brief
** init scene
** @param scene
** @return ** int
*/
int		read_data(t_scene *scene)
{
	scene->camera = camera_default;
	return (0);
}

/**
** @brief
** init sdl window and image buffer
** @param window
** @return ** int
*/
int		init_window(t_window *window)
{
	window->width = DEFAULT_WIDTH; //NOTE: make default value as define
	window->height = DEFAULT_HEIGHT; //NOTE: make default value as define
	window->ptr = SDL_CreateWindow("<3", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, window->width, window->height,
				SDL_WINDOW_RESIZABLE);
	window->renderer = SDL_CreateRenderer(window->ptr, -1,
				SDL_RENDERER_ACCELERATED);
	window->texture = SDL_CreateTexture(window->renderer,
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
				window->width, window->height);
	window->image = (uint32_t *)malloc(sizeof(uint32_t) *
				window->width * window->height);
	return (0);
}

/**
** @brief
** get opencl GPU device
** create opencl context and command queue
** @param clp
** @return ** int
*/
int		init_cl(t_clp *clp)
{
	if (clp == NULL)
		return (1);
	clp->pl_id = NULL;
	clp->de_id = NULL;
	clp->ret = clGetPlatformIDs(1, &(clp->pl_id), &(clp->ret_num_platforms));
	assert(!clp->ret);
	clp->ret = clGetDeviceIDs(clp->pl_id, CL_DEVICE_TYPE_GPU, 1, &(clp->de_id),
						&(clp->ret_num_devices));
	assert(!clp->ret);
	clp->context = clCreateContext(NULL, 1, &(clp->de_id), NULL, NULL,
						&(clp->ret));
	assert(!clp->ret);
	clp->queue = clCreateCommandQueue(clp->context, clp->de_id, 0, &(clp->ret));
	assert(!clp->ret);
	return (0);
}

/**
** @brief
** allocate memory for buffers
** compile opencl program
** @param cl_program
** @return ** int
*/
int		init_renderer(t_cl_program *program)
{
	int		ret;

	init_cl(&program->clp);
	read_kernel(DEFAULT_KERNEL_FILE, &program->source_str);
	program->output = clCreateBuffer(program->clp.context,
		CL_MEM_READ_ONLY, sizeof(uint32_t) * program->work_size, NULL, &ret);
	assert(!ret);
	program->program = clCreateProgramWithSource(program->clp.context, 1,
		(const char **)&program->source_str, NULL, &ret);
	assert(!ret);
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
		NULL, NULL, NULL);
	assert(!ret);
	program->kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
		&ret);
	assert(!ret);
	return (0);
}

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
	init_window(window);
	cl_program->work_size = window->width * window->height;
	cl_program->work_group_size = 128;
	init_renderer(cl_program);
	return 0;
}