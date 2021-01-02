/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:05:43 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:55:40 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# ifdef __APPLE__
#  include <SDL.h>
# elif __unix__
#  include <SDL2/SDL.h>
# else
#  include <SDL.h>
# endif

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif
# include "color.h"

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 640

/*
** @brief
** to manipulate sdl windows
*/

typedef struct s_window	t_window;

struct	s_window
{
	SDL_Window		*ptr;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				width;
	int				height;
};

/*
** @brief
** init sdl window and image buffer
** @param window
** @return ** int
*/

int		init_window(t_window *const window, t_u32 w, t_u32 h);
void	free_window(t_window *const window);

#endif
