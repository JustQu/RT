
float3			discriminant(float a, float b, float d)
{
	float3	ret;
	float	cl;

	cl = -1;
	ret.x = ((-1) * b + sqrt(d)) / (2 * a);
	ret.y = ((-1) * b - sqrt(d)) / (2 * a);
	if (ret.x > 0 && ret.y > 0)
		cl = (ret.x > ret.y) ? ret.y : ret.x;
	else if (ret.x > 0)
		cl = ret.x;
	else if (ret.y > 0)
		cl = ret.y;
	ret.z = cl;
	return (ret);
}

t_obj			new_obj(float3 pnt, float3 dir, float r, int clr, float dif, float ref)
{
	t_obj	slt;

	slt.pnt = pnt;
	slt.dir = dir;
	slt.r = r;
	slt.clr = clr;
	slt.dif = dif;
	slt.ref = ref;
	return (slt);
}
