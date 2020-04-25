t_sampler	get_sampler(t_sampler_manager sampler_manager, int sampler_id)
{
	int			i;
	int			offset;
	t_sampler	tmp;

	offset = 0;
	for (i = 0; i < sampler_id; i++)
	{
		tmp = sampler_manager.samplers[i];
		offset += tmp.num_sets * tmp.num_samples;
	}
	tmp = sampler_manager.samplers[i];
	tmp.offset = offset;
	return (tmp);
}
