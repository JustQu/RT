/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:16:23 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/07 20:58:36 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

void		validate_sphere(t_res_mngr *mngr, t_parsed_info asset, int log)
{
	int		errors;

	errors = 0;
	if (isnan(asset.data.object.r))
	{
		write_logs(RADIUS_DOES_NOT_EXIST, log, "ERROR:");
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

void		validate_torus_disk(t_res_mngr *mngr, t_parsed_info asset, int log)
{
	int		errors;

	errors = 0;
	if (isnan(asset.data.object.r) || isnan(asset.data.object.r2))
	{
		write_logs(RADIUS_DOES_NOT_EXIST, log, "ERROR:");
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

void		validate_triangle_box(t_res_mngr *mngr,
				t_parsed_info asset, int log)
{
	int		errors;

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

void		validate_rectangle(t_res_mngr *mngr, t_parsed_info asset, int log)
{
	int		errors;

	errors = 0;
	if (isnan(asset.data.object.r) || isnan(asset.data.object.r2))
	{
		write_logs(RADIUS_DOES_NOT_EXIST, log, "ERROR:");
		errors++;
	}
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
