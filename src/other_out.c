/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:10:50 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	out_camera(t_camera cam, int fd)
{
	ft_putstr_fd("camera: ", fd);
	out_v3_param(cam.origin, "origin", fd);
	out_v3_param(cam.orient, "orientation", fd);
	out_fparam(cam.fov, "fov", fd);
}

void	output_light(t_light_source l, int fd)
{
	ft_putstr_fd("lightsource: ", fd);
	out_v3_param(l.origin, "origin", fd);
	out_fparam(l.intensity, "intensity", fd);
	ft_putchar_fd('\n', fd);
}

void	output_data(t_param *p)
{
	int		i;

	i = -1;
	while (++i < p->world.nobjs)
		output_obj(p->world.objs[i], p->fd);
	i = -1;
	while (++i < p->world.nlights)
		output_light(p->world.lights[i], p->fd);
	out_camera(p->camera, p->fd);
	ft_putendl_fd("", p->fd);
}
