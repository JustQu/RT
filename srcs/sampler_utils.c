/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:46:47 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/15 16:46:48 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "utils.h"
#include "rt_error.h"

t_sampler	init_sampler(t_sampler_type sampler_type, int num_samples)
{
	t_sampler	sampler;

	sampler.count = 0;
	sampler.jump = 0;
	sampler.type = num_samples == 1 ? regular_grid : sampler_type;
	sampler.num_samples = num_samples ? num_samples : NUM_SAMPLES;
	sampler.num_sets = NUM_SETS;
	if (sampler_type == none)
	{
		sampler.type = sampler_type;
		sampler.num_samples = 1;
		sampler.num_sets = 1;
		return (sampler);
	}
	return (sampler);
}
