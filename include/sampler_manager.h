/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:26:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/04 16:54:26 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLER_MANAGER_H
# define SAMPLER_MANAGER_H

# ifndef __OPENCL_C_VERSION__
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif
# endif

/*
** we should specify the same number of samples for everything
** to avoid artifacts
*/
#define NUM_SAMPLES 256
#define NUM_SETS 83

typedef struct	s_sampler_manager //only on cpu ?
{
	t_sampler		*samplers;

	cl_float3		*hemisphere_samples;
	cl_float2		*samples;
	cl_float2		*disk_samples;

	size_t			samples_size;
	size_t			samples_malloc_size;

///todo: split samples
	size_t			disk_samples_size;
	size_t			disk_samples_malloc_size;

	size_t			hemisphere_samples_size;
	size_t			hemisphere_samples_malloc_size;
///

	size_t			samplers_malloc_size;
	uint32_t		count;

}				t_sampler_manager;


int	new_sampler(t_sampler_manager *sampler_manager,
				t_sampler_type sampler_type,
				int num_samples,
				int num_sets);

int	generate_samples(t_sampler sampler,
					cl_float2 *samples,
					cl_float2 *disk_samples,
					cl_float3 *hemisphere_samples);

#endif
