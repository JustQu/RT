/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 21:48:15 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/20 23:53:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

int					get_light_type_value(char *str)
{
	if (!ft_strcmp(str, "ambient"))
		return (ambient);
	else if (!ft_strcmp(str, "ambient_occluder"))
		return (ambient_occluder);
	else if (!ft_strcmp(str, "directional"))
		return (directional);
	else if (!ft_strcmp(str, "point"))
		return (point);
	else if (!ft_strcmp(str, "area"))
		return (area);
	else if (!ft_strcmp(str, "enviromental"))
		return (enviromental);
	return (ERROR);
}

cl_int				get_coefficient(char *str)
{
	if (!ft_strcmp(str, "no"))
		return (no);
	else if (!ft_strcmp(str, "constant"))
		return (constant);
	else if (!ft_strcmp(str, "occluder"))
		return (occluder);
	return (ERROR);
}

void				get_light_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_light_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_light_type *)v;
	*type = get_light_type_value(str);
}

void				get_ambient_illumination(char *str, int offset, void *data)
{
	unsigned char	*v;
	cl_int			*coefficient;

	v = (unsigned char *)data + offset;
	coefficient = (cl_int *)v;
	*coefficient = get_coefficient(str);
}
