/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:40:30 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:53:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_manager.h"
#include "rt_error.h"
#include "utils.h"

void	init_light_manager(t_light_manager *light_manager)
{
	light_manager->lights = NULL;
	light_manager->nlights = 0;
	light_manager->light_malloc_size = 0;
}

int		add_parsed_light(t_light_manager *light_manager,
						t_parsed_light parsed_light)
{
	t_light	light;

	light.type = parsed_light.type;
	light.origin = parsed_light.origin;
	light.direction = parsed_light.direction;
	light.color = parsed_light.color;
	light.ls = parsed_light.ls;
	light.pdf = parsed_light.pdf;
	light_manager->nlights++;
	if (light_manager->nlights * sizeof(t_light) >=
		light_manager->light_malloc_size)
	{
		light_manager->lights = ft_realloc(light_manager->lights,
			light_manager->light_malloc_size,
			light_manager->nlights * sizeof(t_light) * 2);
		rt_is_dead(system_err, system_malloc_error, !light_manager->lights, "");
		light_manager->light_malloc_size = light_manager->nlights *
			sizeof(t_light) * 2;
	}
	light_manager->lights[light_manager->nlights - 1] = light;
	return (light_manager->nlights - 1);
}
