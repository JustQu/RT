/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 19:14:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/04/25 23:13:04 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

//TODO: make error system

int		init_sampler_manager(t_sampler_manager *sampler_manager)
{
	sampler_manager->count = 0;
	sampler_manager->samplers_malloc_size = 0;
	sampler_manager->samples_size = 0;
	sampler_manager->samples_malloc_size = 0;
	sampler_manager->disk_samples_size = 0;
	sampler_manager->disk_samples_malloc_size = 0;
	sampler_manager->hemisphere_samples_size = 0;
	sampler_manager->hemisphere_samples_malloc_size = 0;
	sampler_manager->samplers = NULL;
	sampler_manager->hemisphere_samples = NULL;
	sampler_manager->samples = NULL;
	sampler_manager->disk_samples = NULL;
}

int		realloc_sampler_manager(t_sampler_manager *sampler_manager, size_t new_size)
{
	cl_float2	*new_samples;
	cl_float2	*new_disk_samples;
	cl_float3	*new_hemisphere_samples;

	if (!(new_samples = malloc(sizeof(cl_float2) * new_size)))
		return (ERROR);
	memcpy(new_samples, sampler_manager->samples, sampler_manager->samples_size * sizeof(cl_float2));
	free(sampler_manager->samples);
	sampler_manager->samples = new_samples;

	if (!(new_disk_samples = malloc(sizeof(cl_float2) * new_size)))
		return (ERROR);
	memcpy(new_disk_samples, sampler_manager->disk_samples, sizeof(cl_float2) * sampler_manager->samples_size);
	free(sampler_manager->disk_samples);
	sampler_manager->disk_samples = new_disk_samples;

	if (!(new_hemisphere_samples = malloc(sizeof(cl_float3) * new_size)))
		return (ERROR);
	memcpy(new_hemisphere_samples, sampler_manager->hemisphere_samples, sizeof(cl_float3) * sampler_manager->samples_size);
	free(sampler_manager->hemisphere_samples);
	sampler_manager->hemisphere_samples = new_hemisphere_samples;

	sampler_manager->samples_malloc_size = new_size;
	return (SUCCESS);
}

int		realloc_samplers(t_sampler_manager *sampler_manager, size_t new_size)
{
	t_sampler *new_samplers;

	if (!(new_samplers = malloc(sizeof(t_sampler) * new_size)))
		return (ERROR);
	memcpy(new_samplers, sampler_manager->samplers, (sampler_manager->count - 1) * sizeof(t_sampler));
	free(sampler_manager->samplers);
	sampler_manager->samplers = new_samplers;
	sampler_manager->samplers_malloc_size = new_size;
	return (SUCCESS);
}

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
		return sampler;
	}
	return sampler;
}
#if 0
int		random_shuffle(void *array, size_t nelems, size_t elem_size)
{
	unsigned char	*p_arr;
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	tmp;
	int				random_index;

	p_arr = (unsigned char *)array;
	for (int i = 0; i < nelems; i++)
	{
		random_index = rand_int() % nelems;
		p1 = p_arr + i * elem_size;
		p2 = p_arr + random_index * elem_size;
		for (int j = 0; j < elem_size; j++)
		{
			tmp = p1[j];
			p1[j] = p2[j];
			p2[j] = tmp;
		}
	}
}

void	setup_shuffled_indices(t_sampler *sampler)
{
	for (int i = 0; i < NUM_SAMPLES; i++) //fill shuffled_indicies array
		sampler->shuffled_indices[i] = i;

	random_shuffle(sampler->shuffled_indices, NUM_SAMPLES, sizeof(*sampler->shuffled_indices));
}
#endif 

/**
** @todo
** samples_type
** @brief
**
** @return sampler_id or -1 if error
*/
int		new_sampler(t_sampler_manager *sampler_manager,
					t_sampler_type sampler_type,
					int num_samples, int samples_type)
{
	t_sampler	sampler;
	int			number;

	sampler = init_sampler(sampler_type, num_samples);
	sampler_manager->count++;
	number = sampler_manager->samples_size + sampler.num_samples * NUM_SETS;

	if (number >= sampler_manager->samples_malloc_size)
		realloc_sampler_manager(sampler_manager, 2 *number);
	if (sampler_manager->count - 1 >= sampler_manager->samplers_malloc_size)
		realloc_samplers(sampler_manager, sampler_manager->count * 2);

	generate_samples(sampler,
					sampler_manager->samples + sampler_manager->samples_size,
					sampler_manager->disk_samples + sampler_manager->samples_size,
					sampler_manager->hemisphere_samples + sampler_manager->samples_size);

	sampler_manager->samples_size += sampler.num_sets * sampler.num_samples;
	// setup_shuffled_indices(&sampler);
	sampler_manager->samplers[sampler_manager->count - 1] = sampler;
	return (sampler_manager->count - 1);
}
