
float2	sample_unit_square(t_sampler *sampler, __global float2 *samples, uint2 *seed)
{
	// if (sampler->count % sampler->num_samples == 0) // ?????? ?????? ???????
	// 	sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((samples + sampler->offset)[sampler->jump +  (random(seed) + sampler->count++) % sampler->num_samples]);

	// return (samples[sampler->jump + sampler->shuffled_indices[sampler->jump + sampler->count++ % sampler->num_samples]]);
}

float2	sample_unit_disk(t_sampler *sampler, __global float2 *disk_samples, uint2 *seed)
{
	// if (sampler->count % sampler->num_samples == 0)
	// 	sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((disk_samples + sampler->offset)[sampler->jump + (random(seed) + sampler->count++) % sampler->num_samples]);;

	// return ((disk_samples + sampler->offset)[sampler->jump + (sampler->count++) % sampler->num_samples]);

	// printf("j: %d %d %d %d %d", sampler->jump, sampler->count, sampler->num_samples, sampler->num_sets, sampler->offset);
	// return ((disk_samples + sampler->offset)[sampler->jump + sampler->count++ % (sampler->num_samples)]);
}

float3	sample_hemisphere(t_sampler *sampler, __global float3 *hemisphere_samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0)
	{
		sampler->jump = (random(seed) % sampler->num_sets)
						* sampler->num_samples;
	}

	return ((hemisphere_samples + sampler->offset)[sampler->jump + (random(seed) + sampler->count++) % sampler->num_samples]);
}
