#include "rt.h"

/**
** @todo
**
*/
void	setup_shuffled_indices(void)
{

}

void	new_sampler(t_sampler *sampler, t_sampler_type type, int num_samples, int num_sets)
{
	sampler->info.num_samples = num_samples;
	sampler->info.num_sets = num_sets;
	if (num_samples > 1)
		sampler->info.type = type;
	else
	{
		sampler->info.type = regular_grid,
		sampler->info.num_samples = 1;
	}
	sampler->sample_set = generate_samples(sampler->info);
}

cl_float2	*generate_rand_jitter_samples(t_sampler_info info)
{
	int n = sqrtf(info.num_samples);
	int index[3];
	int pepa;
	cl_float2 *sp;

	pepa = 0;
	sp = malloc(sizeof(cl_float2) * info.num_sets * info.num_samples);
	for (index[0] = 0; index[0] < info.num_sets; index[0]++)
	{
		for (index[1] = 0; index[1] < n; index[1]++)
		{
			for (index[2] = 0; index[2] < n; index[2]++)
			{
				sp[pepa].x = (index[1] + rand_float()) / n;
				sp[pepa].y = (index[2] + rand_float()) / n;
				pepa++;
				// printf("%d: %f %f\n", pepa, sp[pepa - 1].x, sp[pepa - 1].y);
			}
		}
	}
	return sp;
}

cl_float2	*generate_regular_samples(t_sampler_info info)
{
	int			n = sqrtf(info.num_samples);
	int			index[3];
	int			pepa;
	cl_float2	*sp;

	index[0] = -1;
	index[1] = -1;
	index[2] = -1;
	pepa = 0;
	sp = malloc(sizeof(cl_float2) * info.num_sets * info.num_samples);
	while (++index[0] < info.num_sets && (index[1] = -1))
		while (++index[1] < n && (index[2] = -1))
			while (++index[2] < n)
			{
				sp[pepa].x = (index[1]) / (float)n;
				sp[pepa].y = (index[2]) / (float)n;
				pepa++;
			}
	return (sp);
}

cl_float2	*generate_pure_random_samples(t_sampler_info info)
{
	int n = sqrtf(info.num_samples);
	int index[3];
	int pepa;
	cl_float2 *sp;

	index[0] = -1;
	index[1] = -1;
	index[2] = -1;
	pepa = 0;
	sp = malloc(sizeof(cl_float2) * info.num_sets * info.num_samples);
	while (++index[0] < info.num_sets && (index[1] = -1))
		while (++index[1] < n && (index[2] = -1))
			while (++index[2] < n)
			{
				sp[pepa].x = rand_float();
				sp[pepa].y = rand_float();
				pepa++;
			}
	return (sp);
}

void	shuffle_x_coordinates(cl_float2 *samples, t_sampler_info info)
{
	for (int p = 0; p < info.num_sets; p++)
		for (int i = 0; i < info.num_samples; i++)
		{
			int target = rand() % info.num_samples + p * info.num_samples;
			float temp = samples[i + p * info.num_samples].x;
			samples[i + p * info.num_samples].x = samples[target].x;
			samples[target].x = temp;
		}
}

void	shuffle_y_coordinates(cl_float2 *samples, t_sampler_info info)
{
	for (int p = 0; p < info.num_sets; p++)
		for (int i = 0; i < info.num_samples; i++)
		{
			int target = rand() % info.num_samples + p * info.num_samples;
			float temp = samples[i + p * info.num_samples].y;
			samples[i + p * info.num_samples].y = samples[target].y;
			samples[target].y = temp;
		}
}

cl_float2	*generate_nrooks_samples(t_sampler_info info)
{
	cl_float2	*sp;
	int			pepa;

	pepa = 0;
	sp = malloc(sizeof(cl_float2) * info.num_samples * info.num_sets);
	for (int p = 0; p < info.num_sets; p++)
		for (int j = 0; j < info.num_samples; j++)
		{
			sp[pepa].x = (j + rand_float()) / info.num_samples;
			sp[pepa].y = (j + rand_float()) / info.num_samples;
			pepa++;
			printf("%d: %f %f\n", pepa, sp[pepa - 1].x, sp[pepa - 1].y);
		}
	shuffle_x_coordinates(sp, info);
	// shuffle_y_coordinates(sp, info);
	return sp;
}

/* rand jitter */
cl_float2 *generate_samples(t_sampler_info info)
{
	return generate_nrooks_samples(info);
	return generate_pure_random_samples(info);
	return generate_regular_samples(info);
	// return generate_rand_jitter_samples(info);
}
