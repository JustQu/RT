/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:52:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 17:42:52 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "scene.h"
#include "logs.h"

t_selector		g_selector_cam[] = {
	{"type", offsetof(t_camera, type), get_cam_type},
	{"d", offsetof(t_camera, d), get_float},
	{"direction", offsetof(t_camera, direction), get_vector},
	{"f", offsetof(t_camera, f), get_float},
	{"l", offsetof(t_camera, l), get_float},
	{"origin", offsetof(t_camera, origin), get_vector},
	{"zoom", offsetof(t_camera, zoom), get_float}
};

int			g_cam_selector_size = sizeof(g_selector_cam) / sizeof(t_selector);

void			validate_parsed_camera(t_camera *camera, int log)
{
	if (camera->type == -2)
	{
		camera->type = perspective;
		write_logs(BAD_CAMERA_TYPE, log, "WARNING:");
	}
	if (isnan(camera->origin.x))
	{
		camera->origin = (cl_float4){{0.0f, 1.0f, -8.0f, 0.0f}};
		write_logs(BAD_CAMERA_ORIGIN, log, "WARNING:");
	}
	if (isnan(camera->direction.x))
	{
		camera->direction = (cl_float4){{0.0f, -0.1f, 1.0f, 0.0f}};
		write_logs(BAD_CAMERA_DIRECTION, log, "WARNING:");
	}
	if (isnan(camera->zoom))
	{
		camera->zoom = 0.5f;
		write_logs(BAD_CAMERA_ZOOM, log, "WARNING:");
	}
}

void			fill_camera(char *a, char *b, t_camera *cam)
{
	int			i;

	i = 0;
	while (i < g_cam_selector_size)
	{
		if (!ft_strcmp(g_selector_cam[i].name, a))
		{
			g_selector_cam[i].func(b, g_selector_cam[i].offset, cam);
			break ;
		}
		i++;
	}
}

void			pars_camera(char *str, t_camera *camera, int log)
{
	char		*a;
	char		*b;

	*camera = get_default_camera();
	while (*str != '{' && *str != '\0')
		str++;
	str++;
	while (*str != '\0')
	{
		a = get_key(&str);
		b = get_value(&str);
		while (*str == ';' || *str == '}')
			str++;
		fill_camera(a, b, camera);
		free(a);
		free(b);
	}
	validate_parsed_camera(camera, log);
}
