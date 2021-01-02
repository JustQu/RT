/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs_second.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:40:14 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 12:20:38 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

void		write_logs_9(int num_log, int fd, char *str)
{
	if (num_log == BAD_ROUGHNESS)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Roughness does not exist", fd);
	}
	else if (num_log == BAD_TRANSMISSION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Transmission coefficient does not exist", fd);
	}
	else if (num_log == BAD_SPECULAR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Specular coefficient does not exist", fd);
	}
	else if (num_log == BAD_AMBIENT)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Ambient coefficient does not exist", fd);
	}
	write_logs_10(num_log, fd, str);
}

void		write_logs_8(int num_log, int fd, char *str)
{
	if (num_log == VECTORS_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Bad vectors", fd);
	}
	else if (num_log == BAD_DIFFUSE_COEFFICIEN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Diffuse coefficient does not exist", fd);
	}
	else if (num_log == BAD_INTENSITY)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Intensity does not exist", fd);
	}
	else if (num_log == BAD_REFLECTIVE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Reflective coefficietn does not exist", fd);
	}
	write_logs_9(num_log, fd, str);
}

void		write_logs_7(int num_log, int fd, char *str)
{
	if (num_log == UNKNOWN_OBJ_TYPE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Unkwnown object type", fd);
	}
	else if (num_log == ANGLE_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Angle of cone does not exist", fd);
	}
	else if (num_log == BAD_MINM_MAXM)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Bad minm or maxm", fd);
	}
	else if (num_log == RADIUS_DOES_NOT_EXIST)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Radius does not exist", fd);
	}
	write_logs_8(num_log, fd, str);
}

void		write_logs_6(int num_log, int fd, char *str)
{
	if (num_log == BAD_CAMERA_DIRECTION)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera direction does not exist. Using default", fd);
	}
	else if (num_log == BAD_CAMERA_ZOOM)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera zoom does not exist. Using default", fd);
	}
	else if (num_log == BAD_CAMERA_TYPE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera type does not exist. Using perspective", fd);
	}
	else if (num_log == NO_CAMERA)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera does not exist. Using default camera", fd);
	}
	write_logs_7(num_log, fd, str);
}

void		write_logs_5(int num_log, int fd, char *str)
{
	if (num_log == BAD_SOLID_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Color does not exist. "
		"Using default: {1.0f, 1.0f, 1.0f}", fd);
	}
	else if (num_log == BAD_EVEN_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Even color does not exist. "
		"Using default: {0.5f, 0.5f, 0.5f}", fd);
	}
	else if (num_log == BAD_ODD_COLOR)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Odd color does not exist. "
		"Using default: {0.0f, 0.0f, 1.0f}", fd);
	}
	else if (num_log == BAD_CAMERA_ORIGIN)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Camera origin does not exist. Using default", fd);
	}
	write_logs_6(num_log, fd, str);
}
