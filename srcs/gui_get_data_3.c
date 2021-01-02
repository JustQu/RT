/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_get_data_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 09:58:19 by alex              #+#    #+#             */
/*   Updated: 2020/12/19 13:23:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "libft.h"
#include "rt_error.h"

void			get_illumin_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_3 1");
	if (ptr == 0)
		str[1] = ft_strdup("no");
	else if (ptr == 1)
		str[1] = ft_strdup("constant");
	else if (ptr == 2)
		str[1] = ft_strdup("occluder");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_3 2");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_true_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_3 1");
	if (ptr == 0)
		str[1] = ft_strdup("false");
	else if (ptr == 1)
		str[1] = ft_strdup("true");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_3 2");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_ambient_il_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_3 3");
	if (ptr == 0)
		str[1] = ft_strdup("constant");
	else if (ptr == 1)
		str[1] = ft_strdup("occlusion");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_3 4");
	str[2] = NULL;
	str[3] = NULL;
}

void			get_color_data(t_color color, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_3 5");
	str[1] = itoa_float(color.r);
	str[2] = itoa_float(color.g);
	str[3] = itoa_float(color.b);
}

void			get_rt_type_data(int ptr, char *string, char **str)
{
	str[0] = ft_strdup(string);
	rt_is_dead(system_err, system_malloc_error, !str[0], "gui_get_data_3 6");
	if (ptr == 0)
		str[1] = ft_strdup("ray_caster");
	else if (ptr == 1)
		str[1] = ft_strdup("dir_light");
	else if (ptr == 2)
		str[1] = ft_strdup("path_tracer");
	rt_is_dead(system_err, system_malloc_error, !str[1], "gui_get_data_3 7");
	str[2] = NULL;
	str[3] = NULL;
}
