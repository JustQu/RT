/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 20:15:21 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/21 17:34:48 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sampler_01.h"

cl_float2	*generate_rand_jitter_samples(t_sampler sampler, cl_float2 *samples)
{
	int			n;
	int			i[3];
	int			pepa;
	cl_float2	*sp;

	n = (int)sqrtf((float)sampler.num_samples);
	pepa = 0;
	sp = samples;
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (++(i[0]) < sampler.num_sets)
	{
		while (++(i[1]) < n)
		{
			while (++(i[1]) < n)
			{
				sp[pepa].x = (i[2] + rand_float()) / n;
				sp[pepa].y = (i[1] + rand_float()) / n;
				pepa++;
			}
		}
	}
	return (sp);
}

cl_float2	*generate_regular_samples(t_sampler sampler, cl_float2 *samples)
{
	int			n;
	int			index[3];
	int			pepa;
	cl_float2	*sp;

	n = (int)sqrtf((float)sampler.num_samples);
	index[0] = -1;
	index[1] = -1;
	index[2] = -1;
	pepa = 0;
	sp = samples;
	while (++index[0] < sampler.num_sets && (index[1] = -1))
		while (++index[1] < n && (index[2] = -1))
			while (++index[2] < n)
			{
				sp[pepa].x = (index[2]) / (float)n;
				sp[pepa].y = (index[1]) / (float)n;
				pepa++;
			}
	return (sp);
}

cl_float2	*generate_pure_random_samples(t_sampler sampler, cl_float2 *samples)
{
	int			index[3];
	int			pepa;
	cl_float2	*sp;

	index[0] = -1;
	index[1] = -1;
	pepa = 0;
	sp = samples;
	while (++index[0] < sampler.num_sets && (index[1] = -1))
		while (++index[1] < sampler.num_samples)
		{
			sp[pepa].x = rand_float();
			sp[pepa].y = rand_float();
			pepa++;
		}
	return (sp);
}

void		shuffle_x_coordinates(cl_float2 *samples, t_sampler sampler)
{
	int		target;
	float	temp;
	int		p;
	int		i;

	p = -1;
	while (++p < sampler.num_sets)
	{
		i = -1;
		while (++i < sampler.num_samples)
		{
			target = rand() % sampler.num_samples + p * sampler.num_samples;
			temp = samples[i + p * sampler.num_samples].x;
			samples[i + p * sampler.num_samples].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}

void		shuffle_y_coordinates(cl_float2 *samples, t_sampler sampler)
{
	int		target;
	int		i;
	int		p;
	float	temp;

	p = -1;
	while (++p < sampler.num_sets)
	{
		i = -1;
		while (++i < sampler.num_samples)
		{
			target = rand() % sampler.num_samples + p * sampler.num_samples;
			temp = samples[i + p * sampler.num_samples].y;
			samples[i + p * sampler.num_samples].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}
