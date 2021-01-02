/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:51:48 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:29:39 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef struct s_color	t_color;

/*
** @brief store color in rgb float compnents.
** Components are normolized [0.0f, 1.0f]
*/

struct	s_color
{
	cl_float	r;
	cl_float	g;
	cl_float	b;
	cl_float	a;
};

# ifndef __OPENCL_C_VERSION__

void	set_color_int(t_color *color, int value);
void	set_color_uchar(t_color *color, uint8_t r, uint8_t g, uint8_t b);
void	set_color_float(t_color *color, float r, float g, float b);

# endif

#endif
