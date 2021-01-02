/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:11:31 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/21 13:31:45 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"

t_camera			get_default_camera(void)
{
	t_camera		camera;

	camera.viewplane.pixel_size = 1.0f;
	camera.viewplane.width = 800;
	camera.viewplane.height = 640;
	camera.type = -2;
	camera.origin.x = NAN;
	camera.direction.x = NAN;
	camera.up = (cl_float4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	camera.d = 800;
	camera.zoom = NAN;
	camera.normalized = FALSE;
	return (camera);
}

t_parsed_light		get_default_light(void)
{
	t_parsed_light	light;

	light.type = -2;
	light.origin.x = NAN;
	light.ls = NAN;
	light.color.r = NAN;
	return (light);
}

void				set_default_texture(t_texture *texture)
{
	texture->type = -2;
	texture->data.solid.color.r = NAN;
	texture->data.checker.even.r = NAN;
	texture->data.checker.odd.r = NAN;
	texture->data.smooth_perlin.scale = NAN;
	texture->scale = (cl_float3){{1.0f, 1.0f, 1.0f}};
	texture->translate = (cl_float3){{1.0f, 1.0f, 1.0f}};
}

void				set_default_material(t_material *material)
{
	material->exp = NAN;
	material->is_reflective = 1;
	material->is_transparent = 1;
	material->ka = NAN;
	material->kd = NAN;
	material->kr = NAN;
	material->ks = NAN;
	material->kt = NAN;
	material->reflective_color = (t_color){1.0f, 0.0f, 0.0f, 0.0f};
	material->type = mat_none;
}

t_parsed_object		get_default_obj(void)
{
	t_parsed_object	obj;

	obj.direction.x = NAN;
	set_default_material(&obj.material);
	set_default_texture(&obj.texture);
	obj.maxm = NAN;
	obj.minm = NAN;
	obj.origin.x = NAN;
	obj.r2 = NAN;
	obj.r = NAN;
	obj.rotation.x = NAN;
	obj.scaling = (cl_float3){{1.0f, 1.0f, 1.0f}};
	obj.type = obj_none;
	obj.vector1 = (cl_float4){{NAN, 0.0f, 0.0f, 0.0f}};
	obj.vector2 = (cl_float4){{NAN, 0.0f, 0.0f, 0.0f}};
	return (obj);
}
