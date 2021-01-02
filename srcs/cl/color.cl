t_color	color_sum(t_color a, t_color b)
{
	t_color res;
	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_color	color_multi(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

t_color	float_color_multi(float	c, t_color color)
{
	t_color	res;

	res.r = c * color.r;
	res.g = c * color.g;
	res.b = c * color.b;
	return (res);
}
