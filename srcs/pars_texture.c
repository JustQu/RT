/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:28:12 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/29 20:37:38 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_selector		g_selector_tex[] = {
	{"type", offsetof(t_texture, type), get_tex_type},
	{"color", offsetof(t_texture, data.solid.color), get_color},
	{"odd", offsetof(t_texture, data.checker.odd), get_color},
	{"even", offsetof(t_texture, data.checker.even), get_color},
	{"scale", offsetof(t_texture, scale), get_vector},
	{"translate", offsetof(t_texture, translate), get_vector}
};

int			g_tex_selector_size = sizeof(g_selector_tex) / sizeof(t_selector);

void		fill_texture(char *a, char *b, t_texture *texture)
{
	int		i;

	i = 0;
	while (i < g_tex_selector_size)
	{
		if (!ft_strcmp(g_selector_tex[i].name, a))
		{
			g_selector_tex[i].func(b, g_selector_tex[i].offset, texture);
			break ;
		}
		i++;
	}
}

void		pars_texture(char *str, int offset, void *data)
{
	char			*a;
	char			*b;
	t_texture		*texture;

	texture = (t_texture *)((unsigned char *)data + offset);
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while ((*str == ';' || *str == '}') && *str != '\0')
			str++;
		fill_texture(a, b, texture);
		free(a);
		free(b);
	}
}
