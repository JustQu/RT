/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:24:47 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/20 12:30:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_param(t_param *p)
{
	p->world.nobjs = 0;
	p->world.nlights = 0;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "<3");
	p->img.ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.data = mlx_get_data_addr(p->img.ptr, &p->img.bpp,
	&p->img.size_line, &p->img.endian);
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

int		main(int ac, char **arg)
{
	t_param	p;

	init_param(&p);
	if (!catch_errors(&p, arg, ac))
		return (1);
	world_to_camera(&p);
	rotate_camera(&p);
	render(&p);
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.ptr, 0, 0);
	mlx_hook(p.win_ptr, 2, 0, key_press, &p);
	mlx_hook(p.win_ptr, 4, 0, mouse_press, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
