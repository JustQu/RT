/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:09:12 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	out_plane(t_obj obj, int fd)
{
	t_plane	*plane;

	plane = obj.data;
	ft_putstr_fd("plane: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(plane->nv, "nv", fd);
}

void	out_sphere(t_obj obj, int fd)
{
	t_sphere	*sphere;

	sphere = obj.data;
	ft_putstr_fd("sphere: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_fparam(sphere->radius, "radius", fd);
}

void	out_cone(t_obj obj, int fd)
{
	t_cone	*cone;

	cone = obj.data;
	ft_putstr_fd("cone: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(cone->dir, "direction", fd);
	out_fparam(cone->angle, "angle", fd);
}

void	out_cylinder(t_obj obj, int fd)
{
	t_cylinder	*cyl;

	cyl = obj.data;
	ft_putstr_fd("cylinder: ", fd);
	out_v3_param(obj.origin, "origin", fd);
	out_v3_param(cyl->dir, "direction", fd);
	out_fparam(cyl->radius, "radius", fd);
}

void	output_obj(t_obj obj, int fd)
{
	if (obj.type == plane)
		out_plane(obj, fd);
	else if (obj.type == sphere)
		out_sphere(obj, fd);
	else if (obj.type == cone)
		out_cone(obj, fd);
	else if (obj.type == cylinder)
		out_cylinder(obj, fd);
	ft_putchar_fd('\n', fd);
}
