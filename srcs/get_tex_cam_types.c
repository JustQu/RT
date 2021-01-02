/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_cam_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:35:46 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/20 23:51:12 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"
#include "camera.h"

int					get_tex_type_value(char *str)
{
	if (!ft_strcmp(str, "solid"))
		return (solid);
	else if (!ft_strcmp(str, "checker"))
		return (checker);
	else if (!ft_strcmp(str, "checker2d"))
		return (checker2d);
	else if (!ft_strcmp(str, "transparent_checker"))
		return (transparent_checker);
	else if (!ft_strcmp(str, "reflective_checker"))
		return (reflective_checker);
	else if (!ft_strcmp(str, "perlin"))
		return (perlin);
	else if (!ft_strcmp(str, "smooth_perlin"))
		return (smooth_perlin);
	else if (!ft_strcmp(str, "turbulence_perlin"))
		return (turbulence_perlin);
	else if (!ft_strcmp(str, "wave_perlin"))
		return (wave_perlin);
	else if (!ft_strcmp(str, "image"))
		return (image);
	return (ERROR);
}

int					get_cam_type_value(char *str)
{
	if (!ft_strcmp(str, "orthographic"))
		return (orthographic);
	else if (!ft_strcmp(str, "perspective"))
		return (perspective);
	else if (!ft_strcmp(str, "thin_lens"))
		return (thin_lens);
	else if (!ft_strcmp(str, "fisheye"))
		return (fisheye);
	else if (!ft_strcmp(str, "spherical"))
		return (spherical);
	else if (!ft_strcmp(str, "stereo"))
		return (stereo);
	return (ERROR);
}

void				get_tex_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_texture_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_texture_type *)v;
	*type = get_tex_type_value(str);
}

void				get_cam_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_camera_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_camera_type *)v;
	*type = get_cam_type_value(str);
}
