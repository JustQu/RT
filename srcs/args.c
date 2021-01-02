/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 23:57:55 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 15:29:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

static char const *const	g_usage = "Usage: RT -s file_name\n\
\t[--resolition width heigh]\n\
\t[-N number_of_samples] - only in console mode\n\
\t[--console] - enable console mode\n\
\t[--gpu] - render on gpu\n\
\t[--cpu] - render on cpu\n\
\t[-h] - display help info\n";

static void	usage(void)
{
	ft_putstr(g_usage);
	exit(0);
}

static void	check_args(t_app *app, int ac, int *i, char **av)
{
	if (!ft_strcmp(av[*i], "--resolution"))
	{
		if (*i + 2 >= ac)
			usage();
		app->options.image_width = ft_atoi(av[*i + 1]);
		app->options.image_height = ft_atoi(av[*i + 2]);
		app->options.window_width = ft_atoi(av[*i + 1]);
		app->options.window_height = ft_atoi(av[*i + 2]);
		*i += 2;
	}
	else if (!ft_strcmp(av[*i], "-N"))
		if (*i + 1 == ac)
			usage();
		else
			app->options.num_samples = ft_atoi(av[++(*i)]);
	else if (!ft_strcmp(av[*i], "--img"))
		if (*i + 1 == ac)
			usage();
		else
			app->options.image_file = av[++(*i)];
	else if (!ft_strcmp(av[*i], "--console"))
		app->options.mode = console;
	else
		usage();
}

static void	pars_args(t_app *app, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			if (!ft_strcmp(av[i], "-s"))
			{
				if (i + 1 == ac)
					usage();
				app->options.scene_file = av[i + 1];
				i++;
			}
			else if (!ft_strcmp(av[i], "--gpu"))
				app->options.render_device = CL_DEVICE_TYPE_GPU;
			else if (!ft_strcmp(av[i], "--cpu"))
				app->options.render_device = CL_DEVICE_TYPE_CPU;
			else if (!ft_strcmp(av[i], "-h"))
				usage();
			else
				check_args(app, ac, &i, av);
		else
			usage();
	}
}

/*
** @todo: -s 'scene_file_name';
** 		  --img 'img_name' -N (колво сэмплов);
** 		  -h
** 		  --cpu | --gpu
** 		  --resoulution 1920 1080
**		  --window 800 800
**
** todo:
** 		  --client;
** 		  --server 'ip';
** 		  --gui(by default)
**		  --interface
** @brief
**
** @param app
** @param ac
** @param av
** @return ** void
*/

void		read_av(t_app *app, int ac, char **av)
{
	app->options.render_device = CL_DEVICE_TYPE_DEFAULT;
	app->options.num_samples = NUM_SAMPLES;
	app->options.image_width = DEFAULT_IMAGE_WIDTH;
	app->options.image_height = DEFAULT_IMAGE_HEIGHT;
	app->options.window_width = DEFAULT_WIDTH;
	app->options.window_height = DEFAULT_HEIGHT;
	app->options.scene_file = NULL;
	app->options.enable_gui = TRUE;
	app->options.enable_logs = FALSE;
	app->options.image_file = "image";
	app->options.mode = window_mode;
	if (ac == 2)
	{
		app->options.scene_file = av[1];
	}
	else
	{
		pars_args(app, ac, av);
	}
	rt_is_dead(app_err, app_no_scene_file, !app->options.scene_file, NULL);
}
