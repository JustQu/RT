/**
**TODO: randomness §5
*/
float2	sample_unit_square(__global float2 *sampler_set, t_sampler_info info,
							int *count)
{
	float2	sp;

	sp = sampler_set[*count %
		(info.num_samples * info.num_sets)];
	*count = *count + 1;
	return sp;
}
