/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:00:53 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:48:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>

# include <assert.h>

# ifdef __APPLE__
#  include <SDL.h>
# elif __unix__
#  include <SDL2/SDL.h>
# else
#  include <SDL.h>
# endif

# include "sampler_manager.h"
# include "scene.h"
# include "rt_options.h"
# include "rt_ocl.h"

typedef struct s_rt_options		t_rt_options;

typedef struct s_app			t_app;

typedef struct s_rt				t_rt;

struct							s_rt
{
	t_scene						scene;
	t_sampler_manager			sampler_manager;
	t_rt_options				options;
	t_cl_program				ocl_program;
};

int								init_rt(t_app *app);

void							init_buffers(t_cl_program *const program,
									t_scene *const scene,
									t_sampler_manager *const sampler_manager);

void							render_scene(t_rt rt);

void							read_data(t_scene *scene,
											t_sampler_manager *sampler_manager,
											char *scene_file);

/*
** util functions
*/

float							rand_float();
int								rand_int();
void							swap_int(int *a, int *b);
void							swap_float2(cl_float2 *a, cl_float2 *b);

#endif
