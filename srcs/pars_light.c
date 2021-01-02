/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:56:59 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 15:45:59 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "scene.h"
#include "resource_manager.h"
#include "logs.h"

t_selector			g_selector_light[] = {
	{"origin", offsetof(t_parsed_light, origin), get_vector},
	{"direction", offsetof(t_parsed_light, direction), get_vector},
	{"color", offsetof(t_parsed_light, color), get_color},
	{"ls", offsetof(t_parsed_light, ls), get_float},
	{"type", offsetof(t_parsed_light, type), get_light_type},
};

int					g_light_selector_size = sizeof(g_selector_light) /
sizeof(t_selector);

void				validate_light(t_parsed_info asset,
								t_res_mngr *res_mngr, int log)
{
	int				errors;

	errors = 0;
	if (asset.data.light.type == light_none)
	{
		errors++;
		write_logs(BAD_LIGHT_TYPE, log, "ERROR:");
	}
	if (isnan(asset.data.light.origin.x))
	{
		write_logs(BAD_ORIGIN, log, "WARNING:");
		asset.data.light.origin = (cl_float4){{1000.0f, 1000.0f, 500.0f, 0.0f}};
	}
	if (isnan(asset.data.light.ls))
	{
		write_logs(BAD_INTENSITY, log, "WARNING:");
		asset.data.light.ls = 1.0f;
	}
	if (isnan(asset.data.light.color.r))
	{
		write_logs(BAD_SOLID_COLOR, log, "WARNING:");
		asset.data.light.color = (t_color){1.0f, 1.0f, 1.0f, 0.0f};
	}
	if (errors == 0)
		add_parsed_asset(res_mngr, asset);
}

void				fill_light(char *a, char *b, t_parsed_light *light)
{
	int		i;

	i = 0;
	while (i < g_light_selector_size)
	{
		if (!ft_strcmp(g_selector_light[i].name, a))
		{
			g_selector_light[i].func(b, g_selector_light[i].offset, light);
			break ;
		}
		i++;
	}
}

void				pars_light(char *str, t_parsed_info *asset,
								t_res_mngr *res_mngr, int log)
{
	char			*a;
	char			*b;
	t_parsed_light	light;

	light = get_default_light();
	while (*str != '{' && *str != '\0')
		str++;
	if (*str != '\0')
		str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		fill_light(a, b, &light);
		free(a);
		free(b);
	}
	asset->type = 1;
	asset->data.light = light;
	validate_light(*asset, res_mngr, log);
}
