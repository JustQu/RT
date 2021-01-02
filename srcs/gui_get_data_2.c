/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:26:04 by alex              #+#    #+#             */
/*   Updated: 2020/12/13 15:47:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "camera.h"
#include "libft.h"
#include "rt_error.h"

void			get_void_data(char *string, char *str[4])
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_2 1");
	str[1] = NULL;
	str[2] = NULL;
	str[3] = NULL;
}

void			get_camera_type_data(int ptr, char *string, char *str[4])
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_2 2");
	if (ptr == orthographic)
		str[1] = ft_strdup("orthographic");
	else if (ptr == perspective)
		str[1] = ft_strdup("perspective");
	else if (ptr == thin_lens)
		str[1] = ft_strdup("thin_lens");
	else if (ptr == fisheye)
		str[1] = ft_strdup("fisheye");
	else if (ptr == spherical)
		str[1] = ft_strdup("spherical");
	else if (ptr == stereo)
		str[1] = ft_strdup("stereo");
	else
		str[1] = ft_strdup("material");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_2 3");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_str_data(char *str1, char *string, char *str[4])
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_2 4");
	str[1] = ft_strdup(str1);
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_2 5");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float_data(float ptr, char *string, char *str[4])
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_2 5");
	str[1] = itoa_float(ptr);
	str[2] = NULL;
	str[3] = NULL;
}

void			get_float4_data(cl_float4 ptr, char *string, char *str[4])
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_2 6");
	str[1] = itoa_float(ptr.x);
	str[2] = itoa_float(ptr.y);
	str[3] = itoa_float(ptr.z);
}
