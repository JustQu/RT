/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfalkrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:04:40 by mfalkrea          #+#    #+#             */
/*   Updated: 2020/01/09 17:04:43 by mfalkrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#include <SDL.h>
#else
#include <CL/cl.h>
#include <SDL2/SDL.h>
#endif

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "sizes.h"

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

typedef struct	s_cam
{
	cl_float3	pnt;
	cl_float3	dir;
}				t_cam;

typedef	struct	s_obj
{
	int			type;
	cl_float3	pnt;
	cl_float3	dir;
	float		r;
	int			clr;
	float		dif;
	float		ref;
}				t_obj;

typedef struct	s_sdl
{
	SDL_Renderer	*ren;
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Texture		*tex;
}				t_sdl;

typedef struct	s_rt
{
	char		*name;
	t_sdl		*sdl;
	Uint32		*img;
	t_cam		cam;
	t_obj		*obj;
	unsigned int		num_obj;
	char		*obj_name[5];
}				t_rt;

void 		   ft_clerror(cl_int ret);
cl_program		create_program(cl_context context);

void			open_cl(Uint32 *img, t_cam cam, t_obj *obj, unsigned int num);
int				fd_return(char *name);
float			ft_atoi_float(char *line);
int				next_num(char *line);
cl_float3		read_vec(char *line);
void			init_scene(t_rt	*rt);

#endif
