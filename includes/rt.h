/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:56:36 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/14 15:48:28 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include <SDL.h>
#include <stdio.h>
#include "libft.h"
# include <math.h>
# include "rtmath.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef struct	s_windata
{
	SDL_Renderer	*ren;
	SDL_Window		*win;
}				t_windata;

typedef struct	s_ray
{
	t_vec4		point;
	t_vec4		vec;
}				t_ray;

#endif