/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:43:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/10 19:41:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static const t_camera	camera_default = {
	.origin = {
		.x = 0.0f,
		.y = 2.0f,
		.z = -1.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.ratio = (float)DEFAULT_WIDTH / (float)DEFAULT_HEIGHT,
	.inv_w = 1.0f / DEFAULT_WIDTH,
	.inv_h = 1.0f / DEFAULT_HEIGHT,
	.angle = 1.7320508757,
	.fov = 120
};

static const t_material	default_material = {
	.color = 0x0000afff,
	.kd = 0.5,
	.ks = 0.5,
	.n = 50
};

static const t_obj		default_sphere = {
	.type = sphere,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.r = 1.0f,
	.r2 = 1.0f,
	.material = {
		.color = 0x0076448A,
		.kd = 0.5,
		.ks = 0.5,
		.n = 50
	}
};

static const t_obj		default_plane = {
	.type = plane,
	.origin = {
		.x = 0.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.material = {
		.color = 0x00148869
	}
};

static const t_obj		default_cylinder = {
	.type = cylinder,
	.origin = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.r = 1.0f,
	.r2 = 1.0f,
	.maxm = 1.0f,//max height of cylinder
	.material = {
		.color = 0x001002af
	}
};

static const t_obj default_cone = {
	.type = cone,
	.origin = {
		.x = -3.0f,
		.y = 4.0f,
		.z = 6.0f,
		.w = 0.0f,
	},
	.direction = {
		.x = 0.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.angle = 60.0f * M_PI / 180.0f, //radians
	.r = 0.57735026919,
	.r2 = 1.33333333333, //tan(angle / 2) + 1
	.maxm = 3.0f,
	.minm = 0.0f,//?? this is the right way
	.material = {
		.color = 0x00d4ca19
	}
};

static const t_obj		default_paraboloid = {
	.type = paraboloid,
	.origin = {
		.x = 2.0f,
		.y = 1.0f,
		.z = 5.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.r = 0.3f,
	.minm = 0.0f,
	.maxm = 2.0f,
	.material = {
		.color = 0x05f000f
	}
};

static const t_obj		default_torus = {
	.type = torus,
	.origin = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.direction = {
		.x = 0.0f,
		.y = 0.7071067118f,
		.z = 0.7071067118f,
		.w = 0.0f
	},
	.r = 2.0f,
	.r2 = 0.4f,
	.material = {
		.color = 0x00bf8f0f
	}
};

static const t_triangle	default_triangle = {
	.vertex1 = {
		.x = -1.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.vertex2 = {
		.x = 1.0f,
		.y = -1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.vertex3 = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.vector1 = {
		.x = 2.0f,
		.y = 0.0f,
		.z = 0.0f,
		.w = 0.0f,
	},
	.vector2 = {
		.x = 1.0f,
		.y = 2.0f,
		.z = 0.0f,
		.w = 0.0f
	},
	.normal = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	}
};

static const t_box	default_box = {
	.min ={
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f,
		.w = 0.0f
	},
	.max = {
		.x = 1.0f,
		.y = 1.0f,
		.z = 2.0f,
		.w = 0.0f
	}
};

/**
** @TODO: Maybe rewrite?
** @brief
** считывание opencl кода из файла file_name в строку str
** @param file_name
** @param str
** @return ** size_t
*/
size_t
read_kernel(char *file_name, char **str)
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
	scene->nobjects = 10;
	scene->ntriangles = 1;
	scene->objects = (t_obj *)malloc(sizeof(t_obj) * scene->nobjects);
	scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * scene->ntriangles);
	scene->boxes = (t_box *)malloc(sizeof(t_box));

	//default_scene

	scene->objects[0] = default_plane;

	scene->objects[1] = default_plane;
	scene->objects[1].origin.x = 0.0f;
	scene->objects[1].origin.y = 0.0f;
	scene->objects[1].origin.z = 10.0f;
	scene->objects[1].origin.w = 0.0f;
	scene->objects[1].direction.x = 0.0f;
	scene->objects[1].direction.y = 0.0f;
	scene->objects[1].direction.z = 1.0f;
	scene->objects[1].direction.w = 0.0f;
	scene->objects[1].material.color = 0x00fa00af;

	scene->objects[2] = default_plane;
	scene->objects[2].origin.x = 3.0f;
	scene->objects[2].origin.y = 0.0f;
	scene->objects[2].origin.z = 0.0f;
	scene->objects[2].origin.w = 0.0f;
	scene->objects[2].direction.x = -0.86602540378f;
	scene->objects[2].direction.y = 0.0f;
	scene->objects[2].direction.z = 0.5f;
	scene->objects[2].direction.w = 0.0f;
	scene->objects[2].material.color = 0x0000afaf;

	scene->objects[3] = default_plane;
	scene->objects[3].origin.x = -3.0f;
	scene->objects[3].origin.y = 0.0f;
	scene->objects[3].origin.z = 0.0f;
	scene->objects[3].origin.w = 0.0f;
	scene->objects[3].direction.x = 0.86602540378f;
	scene->objects[3].direction.y = 0.0f;
	scene->objects[3].direction.z = 0.5f;
	scene->objects[3].direction.w = 0.0f;
	scene->objects[3].material.color = 0x00af0f00;

	scene->objects[4] = default_sphere;
	scene->objects[4].origin.x = 5.0f;
	scene->objects[4].origin.y = 5.0f;
	scene->objects[4].origin.z = 7.0f;
	scene->objects[4].r = 2.0f;
	scene->objects[4].r2 = 4.0f;
	scene->objects[4].material.color = 0x003846b0;

	scene->objects[5] = default_cylinder;
	scene->objects[5].origin.x = -1.0f;
	scene->objects[5].origin.y = 5.0f;
	scene->objects[5].origin.z = 7.0f;
	scene->objects[5].direction.x = 1.0f;
	scene->objects[5].direction.y = 0.0f;
	scene->objects[5].direction.z = 0.0f;
	scene->objects[5].maxm = 5.0f;

	scene->objects[6] = default_cone;
	scene->objects[6].material.color = 0x00d4ca19;

	scene->objects[7] = default_paraboloid;

	scene->objects[8] = default_torus;
	scene->objects[8].origin.x = -3.0f;
	scene->objects[8].origin.y = 4.0f;
	scene->objects[8].origin.z = 4.0f;
	scene->objects[8].direction.x = 0.0f;
	scene->objects[8].direction.y = 0.5;
	scene->objects[8].direction.z = 0.86602540378;
	scene->objects[8].r = 1.5f;
	scene->objects[8].r2 = 0.3f;

	scene->objects[9] = default_torus;
	scene->objects[9].origin.x = -2.0f;
	scene->objects[9].origin.y = 5.0f;
	scene->objects[9].origin.z = 4.0f;
	scene->objects[9].direction.x = 0.86602540378f;
	scene->objects[9].direction.y = -0.5;
	scene->objects[9].direction.z = 0;
	scene->objects[9].r = 1.5f;
	scene->objects[9].r2 = 0.3f;

	//
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
	window->width = DEFAULT_WIDTH;
	window->height = DEFAULT_HEIGHT;
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
** get
**  opencl GPU device
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
int		init_renderer(t_cl_program *program, t_scene *scene)
{
	int		ret;

	init_cl(&program->clp);
	read_kernel(DEFAULT_KERNEL_FILE, &program->source_str);
	program->objects = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * scene->nobjects, scene->objects,
		 &ret);
	program->output_image = clCreateBuffer(program->clp.context,
		CL_MEM_READ_WRITE, sizeof(uint32_t) * program->work_size, NULL, &ret);
	assert(!ret);
	program->triangles = clCreateBuffer(program->clp.context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(t_triangle) * scene->ntriangles,
		scene->triangles, &ret);
	assert(!ret);
	program->program = clCreateProgramWithSource(program->clp.context, 1,
		(const char **)&program->source_str, NULL, &ret);
	assert(!ret);
	ret = clBuildProgram(program->program, 1, &program->clp.de_id,
		DEFAULT_KERNEL_INCLUDE, NULL, NULL);
	cl_error(program, &program->clp, ret);
	assert(!ret);
	program->kernel = clCreateKernel(program->program, DEFAULT_KERNEL_NAME,
		&ret);
	cl_error(program, &program->clp, ret);
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
	cl_program->work_group_size = WORK_GROUP_SIZE;
	printf("%d\n", cl_program->work_size);
	init_renderer(cl_program, scene);
	return 0;
}
