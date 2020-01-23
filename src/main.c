/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:27:45 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/23 12:24:07 by dwalda-r         ###   ########.fr       */
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

cl_float4	copyVec4(t_vec4 src)
{
	cl_float4	res;

	res.s[0] = src[0];
	res.s[1] = src[1];
	res.s[2] = src[2];
	res.s[3] = src[3];
	return res;
}

t_materialt	newMaterialt(t_material mat)
{
	t_materialt	nmat;

	nmat.diff_color.s[0] = mat.diff_color.bgra[0];
	nmat.diff_color.s[1] = mat.diff_color.bgra[1];
	nmat.diff_color.s[2] = mat.diff_color.bgra[2];
	nmat.kd = mat.kd;
	nmat.ks = mat.ks;
	nmat.n = mat.n;
	return nmat;
}

t_spheret	*newSpt(t_sphere *oldsp)
{
	t_spheret *sp;

	sp = (t_spheret *)malloc(sizeof(t_spheret));
	sp->radius = oldsp->radius;
	sp->radius2 = oldsp->radius2;
	return sp;
}

t_planet	*newPlanet(t_plane *old)
{
	t_planet	*pl;

	pl = (t_planet *)malloc(sizeof(t_planet));
	pl->nv = copyVec4(old->nv);
	return pl;
}

t_conet		*newConet(t_cone *old)
{
	t_conet	*cn;

	cn = (t_conet *)malloc(sizeof(t_conet));
	cn->dir = copyVec4(old->dir);
	cn->angle = old->angle;
	cn->k = old->k;
	cn->k2 = old->k2;

	return cn;
}

t_cylindert	*newCylindert(t_cylinder *old)
{
	t_cylindert	*cl;

	cl = (t_cylindert *)malloc(sizeof(t_cylindert));
	cl->dir = copyVec4(old->dir);
	cl->radius = old->radius;

	return cl;
}

t_objt	newObjt(t_obj src)
{
	t_objt	newobj;

	newobj.type = src.type;
	newobj.origin = copyVec4(src.origin);
	newobj.mat = newMaterialt(src.mat);
	if (newobj.type == sphere)
		newobj.data = newSpt(src.data);
	else if (newobj.type == plane)
		newobj.data = newPlanet(src.data);
	else if (newobj.type == cone)
		newobj.data = newConet(src.data);
	else if (newobj.type == cylinder)
		newobj.data = newCylindert(src.data);
	return newobj;
}

t_objt *newObjs(t_world w)
{
	t_objt	*objs;
	int		i;

	i = 0;
	objs = (t_objt *)malloc(sizeof(t_objt) * w.nobjs);
	while (i < w.nobjs)
	{
		objs[i] = newObjt(w.objs[i]);
		i++;
	}
	return objs;
}

t_light_sourcet	newLightSourcet(t_light_source old)
{
	t_light_sourcet	ls;

	ls.origin = copyVec4(old.origin);
	ls.intensity = old.intensity;
	return ls;
}

t_light_sourcet	*newLights(t_world w)
{
	t_light_sourcet	*lights;
	int				i;

	i = 0;
	lights = (t_light_sourcet *)malloc(sizeof(t_light_sourcet) * w.nlights);
	while (i < w.nlights)
	{
		lights[i] = newLightSourcet(w.lights[i]);
		i++;
	}
	return lights;
}

t_worldt	*convertData(t_param *p)
{
	t_worldt	*newWorld;

	newWorld = (t_worldt *)malloc(sizeof(t_worldt));
	newWorld->objs = newObjs(p->world);
	newWorld->lights = newLights(p->world);
	newWorld->nlights = p->world.nlights;
	newWorld->nobjs = p->world.nobjs;
	return newWorld;
}

void gradient(t_clp *clp, Uint32 *img, t_param *p)
{
	t_worldt	*newWorld;

	newWorld = convertData(p);
	int i = 0;
	printf("%lu, %lu, %lu\n", sizeof(t_worldt), sizeof(int), sizeof(t_light_sourcet *));
	char *source_str;

	const t_worldt jojo = *(convertData(p));


	size_t source_size = read_kernel("render_kernel.cl", &source_str);
	cl_mem c_mem_obj = clCreateBuffer(clp->context, CL_MEM_WRITE_ONLY, GLOBAL_SIZE * sizeof(int), NULL, &clp->ret);
	cl_mem w_mem_obj = clCreateBuffer(clp->context, CL_MEM_USE_HOST_PTR, sizeof(t_worldt), newWorld, &clp->ret);
	// clEnqueueWriteBuffer(clp->queue, w_mem_obj, CL_TRUE, 0, sizeof(t_worldt), newWorld, 0, NULL, NULL);
	cl_program program = clCreateProgramWithSource(clp->context, 1, (const char **)&source_str, (const size_t *)&source_size, &clp->ret);
	clp->ret = clBuildProgram(program, 1, &clp->de_id, "-I./includes", NULL, NULL);
	size_t len = 0;
	cl_int ret = CL_SUCCESS;
	ret = clGetProgramBuildInfo(program, clp->de_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
	char *buffer = calloc(len, sizeof(char));
	ret = clGetProgramBuildInfo(program, clp->de_id, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
	printf("%s\n",buffer);
	cl_kernel kernel = clCreateKernel(program, "render", &clp->ret);
	clp->ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&c_mem_obj);
	clp->ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&w_mem_obj);
	clp->ret = clSetKernelArg(kernel, 2, sizeof(t_worldt), (void *)&jojo);

	size_t global_item_size = GLOBAL_SIZE;
	size_t local_item_size = 64;
	clp->ret = clEnqueueNDRangeKernel(clp->queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	clp->ret = clEnqueueReadBuffer(clp->queue, c_mem_obj, CL_TRUE, 0, GLOBAL_SIZE * sizeof(int), img, 0, NULL, NULL);
}

t_rectangle	newRectangle(int x, int y, int w, int h)
{
	t_rectangle r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void	drawRectangle(Uint32 *img, t_color color, t_rectangle rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < SCREEN_HEIGHT && i < rect.h + rect.y)
	{
		j = rect.x;
		while (j < SCREEN_WIDTH && j < rect.w + rect.x)
			img[i * SCREEN_WIDTH + j++] = color.color;
		i++;
	}
}

float	distance(int x, int y, int x1 , int y1)
{
	return sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
}

void	drawRectangleRounded(Uint32 *img, t_color color,
		t_rectangle rect, float round)
{
	int	i;
	int	j;
	int	cmp1;
	int	cmp2;

	cmp1 = rect.h + rect.y;
	cmp2 = rect.w + rect.x;
	i = rect.y;
	round = (sqrtf(rect.w * rect.w + rect.h * rect.h) / 2) * ((100 - round) * 0.01);
	while (i < SCREEN_HEIGHT && i < cmp1)
	{
		j = rect.x;
		while (j < SCREEN_WIDTH && j < cmp2)
		{
			if (distance(rect.w / 2 + rect.x, rect.h / 2 + rect.y, j, i) < round)
				img[i * SCREEN_WIDTH + j] = color.color;
			j++;
		}
		i++;
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
	drawRectangle(p->img, (t_color)255, newRectangle(0, 0, SCREEN_WIDTH, 50));
	drawRectangle(p->img, (t_color)0, newRectangle(10, 15, BUTW, BUTH));

	// render(p);
	// gpurender(p);
	// gradient(p->clprm, p->img, p);
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