/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:26:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:47:41 by dmelessa         ###   ########.fr       */
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

# include "sampler.h"

# define NUM_SAMPLES 1
# define NUM_SETS 83

typedef struct		s_sampler_manager
{
	t_sampler		*samplers;

	cl_float3		*hemisphere_samples;
	cl_float2		*samples;
	cl_float2		*disk_samples;

	size_t			samples_size;
	size_t			samples_malloc_size;

	size_t			disk_samples_size;
	size_t			disk_samples_malloc_size;

	size_t			hemisphere_samples_size;
	size_t			hemisphere_samples_malloc_size;

	size_t			samplers_malloc_size;
	uint32_t		count;
	t_u8			gap[12];
}					t_sampler_manager;

int					init_sampler_manager(t_sampler_manager *sampler_manager);

int					new_sampler(t_sampler_manager *sampler_manager,
								t_sampler_type sampler_type,
								int num_samples,
								int num_sets);

int					generate_samples(t_sampler sampler,
									cl_float2 *samples);

#endif
