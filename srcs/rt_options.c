/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 21:37:09 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 00:27:44 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_options.h"
#include "sampler_manager.h"

/*
** todo: перенести в сэттер sampler manager
*/

int		init_default_options(t_rt_options *options,
							t_sampler_manager *sampler_manager)
{
	options->reset = 1;
	options->shadows = TRUE;
	options->ambient_illumination = 0;
	set_color_float(&options->background_color, 0.0f, 0.0f, 0.0f);
	options->depth = 2;
	options->spp = NUM_SAMPLES;
	options->aa_id = new_sampler(sampler_manager, nrooks, 16384,
				DEFAULT_SAMPLES | DISK_SAMPLES | HEMISPHERE_SAMPLES);
	options->tracer_type = ray_caster;
	options->strategy = 1;
	return (SUCCESS);
}
