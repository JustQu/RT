/**
**TODO: randomness §5
*/
float2	sample_unit_square(t_sampler *sampler, __global float2 *samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0)
		sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((samples + sampler->offset)[sampler->jump + sampler->count++ % sampler->num_samples]);

	// return (samples[sampler->jump + sampler->shuffled_indices[sampler->jump + sampler->count++ % sampler->num_samples]]);
}

// float2	sampler_unit_square1(__global float2 *samples, int jump);

/*
**
*/
float2	sample_unit_disk(t_sampler *sampler, __global float2 *disk_samples, uint2 *seed)
{
	if (sampler->count % sampler->num_samples == 0)
		sampler->jump = (random(seed) % sampler->num_sets) * sampler->num_samples;

	return ((disk_samples + sampler->offset)[sampler->jump + sampler->count++ % sampler->num_samples]);
}
