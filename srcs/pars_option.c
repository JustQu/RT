/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:55:24 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/30 15:29:56 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "resource_manager.h"

t_selector		g_selector_opt[] = {
	{"background_color", offsetof(t_rt_options, background_color), get_color},
	{"depth", offsetof(t_rt_options, depth), get_int},
	{"shadows", offsetof(t_rt_options, shadows), get_uchar},
	{"area_lightning", offsetof(t_rt_options, area_lightning), get_int},
	{"spp", offsetof(t_rt_options, spp), get_float},
	{"aa_id", offsetof(t_rt_options, aa_id), get_int},
	{"ambient_illumination", offsetof(t_rt_options, ambient_illumination),
		get_ambient_illumination},
	{"tracer_type", offsetof(t_rt_options, tracer_type), get_tracer_type},
	{"strategy", offsetof(t_rt_options, strategy), get_int}
};

int			g_opt_selector_size = sizeof(g_selector_opt) / sizeof(t_selector);

void			fill_options(char *a, char *b, t_res_mngr *mngr)
{
	int			i;

	i = 0;
	while (i < g_opt_selector_size)
	{
		if (!ft_strcmp(g_selector_opt[i].name, a))
		{
			g_selector_opt[i].func(b, g_selector_opt[i].offset,
				mngr->rt_options);
			break ;
		}
		else if (!ft_strcmp(a, "ambient_coefficient"))
		{
			mngr->scene->ambient_occluder.ls = ft_atofloat(b);
			mngr->scene->ambient_light.ls = mngr->scene->ambient_occluder.ls;
			break ;
		}
		else if (!ft_strcmp(a, "ambient_occlusion"))
		{
			get_color(b, 0, &mngr->scene->ambient_occluder.min_amount);
			break ;
		}
		i++;
	}
}

void			pars_options(char *str, t_res_mngr *mngr)
{
	char		*a;
	char		*b;

	while (*str != '{' && *str != '\0')
		str++;
	if (*str != '\0')
		str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while ((*str == ';' || *str == '}') && *str != '\0')
			str++;
		fill_options(a, b, mngr);
		free(a);
		free(b);
	}
}
