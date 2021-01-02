/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:53:59 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 00:13:03 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLER_H
# define SAMPLER_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef enum e_sampler_type	t_sampler_type;
typedef struct s_sampler	t_sampler;

enum						e_sampler_type
{
	none,
	regular_grid,
	jitter,
	rand_jitter,
	pure_random,
	nrooks
};

/*
** Sample types flags
*/

# define DEFAULT_SAMPLES		1 << 0
# define DISK_SAMPLES		1 << 1
# define HEMISPHERE_SAMPLES	1 << 2

/*
** num_sampler - number of sample points in a pattern
** num_sets - number of sample set(patterns)
** count - current number of sample points used
** jump - random index jump
*/

struct						s_sampler
{
	t_sampler_type			type;
	cl_int					num_samples;
	cl_int					num_sets;
	cl_uint					count;
	cl_int					jump;
	cl_int					samples_type;
	cl_int					offset;
	cl_int					disk_samples_offset;
	cl_int					hemisphere_samples_offset;
	cl_int					gap[3];
};

# ifndef __OPENCL_C_VERSION__

void						map_samples_to_unit_disk(t_sampler sampler,
					cl_float2 *samples,
					cl_float2 *disk_samples);
void						map_samples_to_hemisphere(t_sampler sampler,
					cl_float2 *samples,
					cl_float3 *hemisphere_samples, const float e);

# endif

#endif
