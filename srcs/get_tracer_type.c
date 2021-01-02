/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tracer_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:28:18 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/20 23:55:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offset.h"
#include "parser.h"

int					get_tracer_type_value(char *str)
{
	if (!ft_strcmp(str, "path_tracer"))
		return (path_tracer);
	else if (!ft_strcmp(str, "ray_caster"))
		return (ray_caster);
	else if (!ft_strcmp(str, "direct_lightning"))
		return (direct_lightning);
	return (ray_caster);
}

void				get_tracer_type(char *str, int offset, void *data)
{
	unsigned char	*v;
	t_tracer_type	*type;

	v = (unsigned char *)data + offset;
	type = (t_tracer_type *)v;
	*type = get_tracer_type_value(str);
}
