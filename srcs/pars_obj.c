/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 21:41:52 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/14 22:13:17 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"
#include "offset.h"
#include "resource_manager.h"

t_selector		g_selector_obj[] = {
	{"origin", offsetof(t_parsed_object, origin), get_vector},
	{"direction", offsetof(t_parsed_object, direction), get_vector},
	{"rotation", offsetof(t_parsed_object, rotation), get_vector},
	{"scaling", offsetof(t_parsed_object, scaling), get_vector},
	{"vector1", offsetof(t_parsed_object, vector1), get_vector},
	{"vector2", offsetof(t_parsed_object, vector2), get_vector},
	{"type", offsetof(t_parsed_object, type), get_obj_type},
	{"radius", offsetof(t_parsed_object, r), get_float},
	{"radius2", offsetof(t_parsed_object, r2), get_float},
	{"maxm", offsetof(t_parsed_object, maxm), get_float},
	{"minm", offsetof(t_parsed_object, minm), get_float},
	{"material", offsetof(t_parsed_object, material), pars_material},
	{"texture", offsetof(t_parsed_object, texture), pars_texture}
};

int				g_obj_selector_size = sizeof(g_selector_obj) /
sizeof(t_selector);

void			validate_parsed_obj_2(t_res_mngr *resource_manager,
				t_parsed_info asset, int log)
{
	if (asset.data.object.type == cone)
		validate_cone(resource_manager, asset, log);
	else if (asset.data.object.type == cylinder)
		validate_cylinder(resource_manager, asset, log);
	else if (asset.data.object.type == paraboloid)
		validate_paraboloid(resource_manager, asset, log);
	else if (asset.data.object.type == plane)
		validate_plane(resource_manager, asset, log);
	else if (asset.data.object.type == sphere)
		validate_sphere(resource_manager, asset, log);
	else if (asset.data.object.type == torus || asset.data.object.type == disk)
		validate_torus_disk(resource_manager, asset, log);
	else if (asset.data.object.type == triangle || asset.data.object.type
		== box)
		validate_triangle_box(resource_manager, asset, log);
	else if (asset.data.object.type == rectangle)
		validate_rectangle(resource_manager, asset, log);
}

void			validate_parsed_obj(t_res_mngr *resource_manager,
				t_parsed_info asset, int log)
{
	if (asset.data.object.type == -2)
	{
		write_logs(OBJ_TYPE_DOES_NOT_EXIST, log, "ERROR:");
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	else if (asset.data.object.type == -1)
	{
		write_logs(UNKNOWN_OBJ_TYPE, log, "ERROR:");
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	validate_parsed_obj_2(resource_manager, asset, log);
}

void			fill_object(char *a, char *b, t_parsed_object *obj)
{
	int			i;

	i = 0;
	while (i < g_obj_selector_size)
	{
		if (!ft_strcmp(g_selector_obj[i].name, a))
		{
			g_selector_obj[i].func(b, g_selector_obj[i].offset, obj);
			break ;
		}
		i++;
	}
}

void			pars_object(t_res_mngr *resource_manager,
					t_parsed_info *asset, char *str, int log)
{
	char			*a;
	char			*b;
	t_parsed_object	obj;

	obj = get_default_obj();
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
		fill_object(a, b, &obj);
		free(a);
		free(b);
	}
	asset->data.object = obj;
	asset->type = 0;
	validate_parsed_obj(resource_manager, *asset, log);
}
