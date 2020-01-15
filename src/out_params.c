/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:07:11 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_fnumber(float val, int fd, int fdigits)
{
	char *c;

	c = ft_itoaf(val, fdigits);
	ft_putstr_fd(c, fd);
	ft_strdel(&c);
}

void	out_fparam(float val, char *param, int fd)
{
	ft_putstr_fd(param, fd);
	ft_putchar_fd('(', fd);
	print_fnumber(val, fd, 3);
	ft_putstr_fd(") ", fd);
}

void	out_v3_param(t_vec3 val, char *param, int fd)
{
	ft_putstr_fd(param, fd);
	ft_putchar_fd('(', fd);
	print_fnumber(val[ox], fd, 3);
	ft_putstr_fd(", ", fd);
	print_fnumber(val[oy], fd, 3);
	ft_putstr_fd(", ", fd);
	print_fnumber(val[oz], fd, 3);
	ft_putstr_fd(") ", fd);
}
