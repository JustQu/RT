/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:05:10 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 12:01:22 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

int				validate_default(t_parsed_info *asset, int log)
{
	int			errors;

	errors = 0;
	if (isnan(asset->data.object.origin.x))
	{
		write_logs(BAD_ORIGIN, log, "ERROR:");
		errors++;
	}
	if (isnan(asset->data.object.rotation.x))
	{
		write_logs(BAD_ROTATION, log, "WARNING:");
		asset->data.object.rotation = (cl_float3){{0.0f, 0.0f, 0.0f}};
	}
	return (errors);
}

void			validate_cone(t_res_mngr *mngr, t_parsed_info asset, int log)
{
	int			errors;

	errors = 0;
	if (isnan(asset.data.object.r2))
	{
		write_logs(ANGLE_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	if (isnan(asset.data.object.minm) || isnan(asset.data.object.maxm))
	{
		write_logs(BAD_MINM_MAXM, log, "ERROR:");
		errors++;
	}
	errors += validate_default(&asset, log);
	errors += validate_texture(&asset, log) + validate_material(&asset, log);
	if (errors > 0)
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	write_logs(PARS_SUCCESS, log, NULL);
	add_parsed_asset(mngr, asset);
}

void			validate_cylinder(t_res_mngr *mngr,
					t_parsed_info asset, int log)
{
	int			errors;

	errors = 0;
	if (isnan(asset.data.object.r))
	{
		write_logs(RADIUS_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	if (isnan(asset.data.object.minm) || isnan(asset.data.object.maxm))
	{
		write_logs(BAD_MINM_MAXM, log, "ERROR:");
		errors++;
	}
	errors += validate_default(&asset, log);
	errors += validate_texture(&asset, log) + validate_material(&asset, log);
	if (errors > 0)
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	write_logs(PARS_SUCCESS, log, NULL);
	add_parsed_asset(mngr, asset);
}

void			validate_paraboloid(t_res_mngr *mngr,
					t_parsed_info asset, int log)
{
	int			errors;

	errors = 0;
	if (isnan(asset.data.object.r))
	{
		write_logs(RADIUS_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	if (isnan(asset.data.object.minm) || isnan(asset.data.object.maxm))
	{
		write_logs(BAD_MINM_MAXM, log, "ERROR:");
		errors++;
	}
	errors += validate_default(&asset, log);
	errors += validate_texture(&asset, log) + validate_material(&asset, log);
	if (errors > 0)
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	write_logs(PARS_SUCCESS, log, NULL);
	add_parsed_asset(mngr, asset);
}

void			validate_plane(t_res_mngr *mngr, t_parsed_info asset, int log)
{
	int			errors;

	errors = 0;
	if (isnan(asset.data.object.vector1.x) ||
	isnan(asset.data.object.vector2.x))
	{
		write_logs(VECTORS_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
	errors += validate_default(&asset, log);
	errors += validate_texture(&asset, log) + validate_material(&asset, log);
	if (errors > 0)
	{
		write_logs(PARS_UNSUCCESS, log, NULL);
		return ;
	}
	write_logs(PARS_SUCCESS, log, NULL);
	add_parsed_asset(mngr, asset);
}
