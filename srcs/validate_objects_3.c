/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:58:54 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/14 17:04:14 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

void		validate_forth(t_parsed_info *asset, int log)
{
	if (asset->data.object.material.type == phong)
	{
		if (isnan(asset->data.object.material.kd))
		{
			write_logs(BAD_DIFFUSE_COEFFICIEN, log, "WARNING:");
			asset->data.object.material.kd = 1.0f;
		}
		if (isnan(asset->data.object.material.ks))
		{
			write_logs(BAD_SPECULAR, log, "WARNING:");
			asset->data.object.material.ks = 0.2f;
		}
		if (isnan(asset->data.object.material.exp))
		{
			write_logs(BAD_ROUGHNESS, log, "WARNING:");
			asset->data.object.material.exp = 10.0f;
		}
	}
	else if (asset->data.object.material.type == matte &&
	isnan(asset->data.object.material.kd))
	{
		write_logs(BAD_DIFFUSE_COEFFICIEN, log, "WARNING:");
		asset->data.object.material.kd = 1.0f;
	}
}

void		validate_third(t_parsed_info *asset, int log)
{
	if (asset->data.object.material.type == plastic)
	{
		if (isnan(asset->data.object.material.kd))
		{
			write_logs(BAD_DIFFUSE_COEFFICIEN, log, "WARNING:");
			asset->data.object.material.kd = 1.0f;
		}
		if (isnan(asset->data.object.material.kr))
		{
			write_logs(BAD_REFLECTIVE, log, "WARNING:");
			asset->data.object.material.kr = 1.0f;
		}
		if (isnan(asset->data.object.material.exp))
		{
			write_logs(BAD_ROUGHNESS, log, "WARNING:");
			asset->data.object.material.exp = 0.1f;
		}
	}
	if (isnan(asset->data.object.material.ka))
	{
		write_logs(BAD_AMBIENT, log, "WARNING");
		asset->data.object.material.ka = 0.0f;
	}
	validate_forth(asset, log);
}

void		validate_second(t_parsed_info *asset, int log)
{
	if (asset->data.object.material.type == mirror &&
	isnan(asset->data.object.material.kr))
	{
		write_logs(BAD_REFLECTIVE, log, "WARNING:");
		asset->data.object.material.kr = 1.0f;
	}
	else if (asset->data.object.material.type == conductor)
	{
		if (isnan(asset->data.object.material.kr))
		{
			write_logs(BAD_REFLECTIVE, log, "WARNING:");
			asset->data.object.material.kr = 1.0f;
		}
		if (isnan(asset->data.object.material.exp))
		{
			write_logs(BAD_ROUGHNESS, log, "WARNING:");
			asset->data.object.material.exp = 0.1f;
		}
	}
	else if (asset->data.object.material.type == emissive &&
	isnan(asset->data.object.material.ls))
	{
		write_logs(BAD_INTENSITY, log, "WARNING:");
		asset->data.object.material.ls = 15.0f;
	}
}

int			validate_material(t_parsed_info *asset, int log)
{
	int		errors;

	errors = 0;
	if (asset->data.object.material.type == mat_none)
	{
		write_logs(MATERIAL_TYPE_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	else if (asset->data.object.material.type == dielectric)
	{
		if (isnan(asset->data.object.material.kt))
		{
			write_logs(BAD_TRANSMISSION, log, "WARNING:");
			asset->data.object.material.kt = 2.4f;
		}
		if (isnan(asset->data.object.material.exp))
		{
			write_logs(BAD_ROUGHNESS, log, "WARNING:");
			asset->data.object.material.exp = 0.1f;
		}
	}
	validate_second(asset, log);
	validate_third(asset, log);
	return (errors);
}

int			validate_texture(t_parsed_info *asset, int log)
{
	int		errors;

	errors = 0;
	if (asset->data.object.texture.type == tex_none)
	{
		write_logs(TEXTURE_TYPE_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	else if (asset->data.object.texture.type == checker &&
	(isnan(asset->data.object.texture.data.checker.even.r) ||
	isnan(asset->data.object.texture.data.checker.odd.r)))
	{
		write_logs(COLOR_DOES_NOT_EXIST, log, "WARNING:");
		asset->data.object.texture.data.checker.even =
											(t_color){0.5f, 0.5f, 0.5f, 0.0f};
		asset->data.object.texture.data.checker.odd =
											(t_color){0.0f, 0.0f, 1.0f, 0.0f};
	}
	else if (isnan(asset->data.object.texture.data.solid.color.r))
	{
		write_logs(COLOR_DOES_NOT_EXIST, log, "WARNING:");
		asset->data.object.texture.data.solid.color =
											(t_color){1.0f, 1.0f, 1.0f, 0.0f};
	}
	return (errors);
}
