#include "rt.h"

cl_float2	*generate_rand_jitter_samples(t_sampler sampler, cl_float2 *samples)
{
	int			n = sqrtf(sampler.num_samples);
	int			index[3];
	int			pepa;
	cl_float2	*sp;

	pepa = 0;
	sp = samples;
	for (index[0] = 0; index[0] < sampler.num_sets; index[0]++)
	{
		for (index[1] = 0; index[1] < n; index[1]++)
		{
			for (index[2] = 0; index[2] < n; index[2]++)
			{
				sp[pepa].x = (index[2] + rand_float()) / n;
				sp[pepa].y = (index[1] + rand_float()) / n;
				pepa++;
			}
		}
	}
	return sp;
}

cl_float2	*generate_regular_samples(t_sampler sampler, cl_float2 *samples)
{
	int			n = sqrtf(sampler.num_samples);
	int			index[3];
	int			pepa;
	cl_float2	*sp;

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
	int			n = sqrtf(sampler.num_samples);
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

void	shuffle_x_coordinates(cl_float2 *samples, t_sampler sampler)
{
	for (int p = 0; p < sampler.num_sets; p++)
		for (int i = 0; i < sampler.num_samples; i++)
		{
			int target = rand() % sampler.num_samples + p * sampler.num_samples;
			float temp = samples[i + p * sampler.num_samples].x;
			samples[i + p * sampler.num_samples].x = samples[target].x;
			samples[target].x = temp;
		}
}

void	shuffle_y_coordinates(cl_float2 *samples, t_sampler sampler)
{
	for (int p = 0; p < sampler.num_sets; p++)
		for (int i = 0; i < sampler.num_samples; i++)
		{
			int target = rand() % sampler.num_samples + p * sampler.num_samples;
			float temp = samples[i + p * sampler.num_samples].y;
			samples[i + p * sampler.num_samples].y = samples[target].y;
			samples[target].y = temp;
		}
}

cl_float2	*generate_nrooks_samples(t_sampler info, cl_float2 *samples)
{
	cl_float2	*sp;
	int			pepa;

	pepa = 0;
	sp = samples;
	for (int p = 0; p < info.num_sets; p++)
		for (int j = 0; j < info.num_samples; j++)
		{
			sp[pepa].x = (j + rand_float()) / info.num_samples;
			sp[pepa].y = (j + rand_float()) / info.num_samples;
			pepa++;
		}
	shuffle_x_coordinates(sp, info);
	shuffle_y_coordinates(sp, info);
	return sp;
}

/**
** @brief
** We require sample points distributed on a unit disk for the simulation of
** the depth of field with circular camera lens and for shading with disk lights
** @param sampler
** @return ** cl_float2*
*/
void	map_samples_to_unit_disk(t_sampler sampler, cl_float2 *samples, cl_float2 *disk_samples)
{
	float		r;
	float		phi;
	cl_float2	sp;
	int			size;

	size = sampler.num_samples * sampler.num_sets;
	for (int j = 0; j < size; j++)
	{
		sp.x = 2.0 * samples[j].x - 1.0;
		sp.y = 2.0 * samples[j].y - 1.0;
		if (sp.x > -sp.y)
		{
			r = sp.x > sp.y ? sp.x : sp.y;
			phi = sp.x > sp.y ? sp.y / sp.x : 2 - sp.x / sp.y;
		}
		else
		{
			if (sp.x < sp.y)
			{
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else
			{
				r = -sp.y;
				if (sp.y != 0.0f)
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0f;
			}
		}
		phi *= M_PI / 4.0f;
		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}
}

/**
** @brief
** use to simulate ambient occlusion, enviromental lights, glossy reflection
** and diffuse-diffuse light transport
** @param sampler
** @return ** void
*/
void	map_samples_to_hemisphere(t_sampler sampler, cl_float2 *samples, cl_float3 *hemisphere_samples, const float e)
{
	int			size;
	cl_float3	sp;
	float		cos_phi;
	float		sin_phi;

	size = sampler.num_samples * sampler.num_sets;
	for (int j = 0; j < size; j++)
	{
		cos_phi = cos(2.0 * M_PI * samples[j].x);
		sin_phi = sin(2.0 * M_PI * samples[j].x);
		sp.x = cos_phi * sqrt(1.0 - pow(pow((1.0 - samples[j].y),
										1.0 / (e + 1.0)), 2));
		sp.y = sin_phi * sqrt(1.0 - pow(pow((1.0 - samples[j].y),
										1.0 / (e + 1.0)), 2));
		sp.z = pow((1.0 - samples[j].y), 1.0 / (e + 1.0));
		hemisphere_samples[j] = sp;
	}
}

int		generate_samples(t_sampler sampler,
						cl_float2 *samples,
						cl_float2 *disk_samples,
						cl_float3 *hemisphere_samples)
{
	if (sampler.type == regular_grid)
	{
		generate_regular_samples(sampler, samples);
	}
	else if (sampler.type == rand_jitter)
	{
		generate_rand_jitter_samples(sampler, samples);
	}
	else if (sampler.type == pure_random)
	{
		generate_pure_random_samples(sampler, samples);
	}
	else if (sampler.type == nrooks)
	{
		generate_nrooks_samples(sampler, samples);
	}
	else
	{
		return ;
	}
	map_samples_to_unit_disk(sampler, samples, disk_samples);
	map_samples_to_hemisphere(sampler, samples, hemisphere_samples, 1.0f);
}
