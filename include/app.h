/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:02:27 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:48:40 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

/*
** Main header of the app.
** Include other parts of programm
*/

# include "rt.h"
# include "window.h"
# include "image.h"
# include "interface.h"
# include "parser.h"
# include "resource_manager.h"
# include "rt_error.h"
# include "state.h"

typedef struct s_app			t_app;
typedef struct s_app_options	t_app_opt;

struct							s_app_options
{
	char						*scene_file;

	int							num_samples;

	int							enable_gui;
	int							mode;
	int							interface;

	t_u32						window_width;
	t_u32						window_height;

	int							render_device;

	int							enable_logs;
	char						*log_file;

	char						*image_file;
	t_u32						image_width;
	t_u32						image_height;
};

/*
** mode: 0 - gui, 1 - console
** todo: interface struct
*/

struct							s_app
{
	t_res_mngr					resource_manager;
	t_rt						rt;
	t_window					window;
	t_interface					interface;

	t_app_opt					options;

	t_image						image;

	t_s32						render_mode;
};

void							read_av(t_app *app, int ac, char **av);

void							loading_screen(t_cl_program *p,
												t_window *window);

/*
** event_functions
*/

int								catch_event(t_rt *rt,
											t_window *win,
											t_interface *interface);
int								catch_keydown(t_rt *rt, t_interface *interface,
											SDL_Event event);

void							display_info(t_interface *const interface,
											t_res_mngr *const mngr,
											t_window *const window);

/*
** Initialization of our app
*/

int								init_app(t_app *app);

/*
** Cleaning everything on exit
*/

void							cleanup(t_app app);

/*
** Error functions
*/

void							cl_error(t_cl_program *program, t_clp *clp,
										int code);

#endif
