/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:02:56 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:32:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sampler_01.h"

cl_float2		*generate_nrooks_samples(t_sampler info, cl_float2 *samples)
{
	cl_float2	*sp;
	int			pepa;
	int			ctr[2];

	ctr[0] = -1;
	pepa = 0;
	sp = samples;
	while (++(ctr[0]))
	{
		ctr[1] = -1;
		while (++(ctr[1]))
		{
			sp[pepa].x = (ctr[1] + rand_float()) / info.num_samples;
			sp[pepa].y = (ctr[1] + rand_float()) / info.num_samples;
			pepa++;
		}
	}
	shuffle_x_coordinates(sp, info);
	shuffle_y_coordinates(sp, info);
	return (sp);
}

/*
** @brief
** We require sample points distributed on a unit disk for the simulation of
** the depth of field with circular camera lens and for shading with disk lights
** @param sampler
** @return ** cl_float2*
*/

static void		extra_for_loop(cl_float2 *sp, float *r, float *phi)
{
	if (sp->x < sp->y)
	{
		*r = -sp->x;
		*phi = 4.0f + sp->y / sp->x;
	}
	else
	{
		*r = -sp->y;
		if (sp->y != 0.0f)
			*phi = 6 - sp->x / sp->y;
		else
			*phi = 0.0f;
	}
}

void			map_samples_to_unit_disk(t_sampler sampler, cl_float2 *samples,
							cl_float2 *disk_samples)
{
	float		r;
	float		phi;
	cl_float2	sp;
	int			size[2];

	size[0] = -1;
	size[1] = sampler.num_samples * sampler.num_sets;
	while (++(size[0]) < size[1])
	{
		sp.x = 2.0f * samples[size[0]].x - 1.0f;
		sp.y = 2.0f * samples[size[0]].y - 1.0f;
		if (sp.x > -sp.y)
		{
			r = sp.x > sp.y ? sp.x : sp.y;
			phi = sp.x > sp.y ? sp.y / sp.x : 2 - sp.x / sp.y;
		}
		else
			extra_for_loop(&sp, &r, &phi);
		phi *= (float)M_PI / 4.0f;
		disk_samples[size[0]].x = r * cosf(phi);
		disk_samples[size[0]].y = r * sinf(phi);
	}
}

/*
** @brief
** use to simulate ambient occlusion, enviromental lights, glossy reflection
** and diffuse-diffuse light transport
** @param sampler
** @return ** void
*/

void			map_samples_to_hemisphere(t_sampler sampler, cl_float2 *samples,
								cl_float3 *hemisphere_samples, const float e)
{
	int			size[2];
	cl_float3	sp;
	float		cos_phi;
	float		sin_phi;

	size[0] = -1;
	size[1] = sampler.num_samples * sampler.num_sets;
	while (++(size[0]) < size[1])
	{
		cos_phi = cosf(2.0f * (float)M_PI * samples[size[0]].x);
		sin_phi = sinf(2.0f * (float)M_PI * samples[size[0]].x);
		sp.x = cos_phi * sqrtf(1.0f - powf(powf((1.0f - samples[size[0]].y),
										1.0f / (e + 1.0f)), 2.0f));
		sp.y = sin_phi * sqrtf(1.0f - powf(powf((1.0f - samples[size[0]].y),
										1.0f / (e + 1.0f)), 2.0f));
		sp.z = powf((1.0f - samples[size[0]].y), 1.0f / (e + 1.0f));
		hemisphere_samples[size[0]] = sp;
	}
}

int				generate_samples(t_sampler sampler,
						cl_float2 *samples)
{
	if (sampler.type == regular_grid)
		generate_regular_samples(sampler, samples);
	else if (sampler.type == rand_jitter)
		generate_rand_jitter_samples(sampler, samples);
	else if (sampler.type == pure_random)
		generate_pure_random_samples(sampler, samples);
	else if (sampler.type == nrooks)
		generate_nrooks_samples(sampler, samples);
	else
		return (0);
	return (SUCCESS);
}
