
typedef struct	s_cal_clr
{
	float3		*k;
	float3		*sm_clr;
}				t_cal_clr;

float3	compare(float3 a, float n)
{
	if (a.x > n)
		a.x = n;
	if (a.y > n)
		a.y = n;
	if (a.z > n)
		a.z = n;
	return (a);
}

void	add_if(float3 *k, float3 tmp)
{
	if (tmp.x > 0)
		k->x += tmp.x;
	if (tmp.y > 0)
		k->y += tmp.y;
	if (tmp.z > 0)
		k->z += tmp.z;
}

int		is_shadow(float3 pnt, float3 lgt_pnt, __global const t_obj *obj, const int num_obj)
{
	t_obj	slt;
	t_cam	ray;
	float3	dir;

	dir = lgt_pnt - pnt;
	ray.pnt = pnt;
	ray.dir = dir;
	slt = closest_figure(ray, obj, num_obj);
	if (slt.dir.x == 0 && slt.dir.y == 0 && slt.dir.z == 0)
		return (0);
	else if (dot(pnt - slt.pnt, pnt - slt.pnt) > dot(dir, dir))
		return (0);
	return (1);
}

void	for_every_light(t_obj slt, t_obj lgt, t_cal_clr c, const t_cam cam, __global const t_obj *obj, const int num_obj)
{
	float3	n;
	float3	l;
	float3	tmp;
	float	dif;

	if (!is_shadow(slt.pnt, lgt.pnt, obj, num_obj))
	{
		n = normalize(slt.dir);
		l = normalize(lgt.pnt - slt.pnt);
		tmp.x = dot(l, n) * ((float)((lgt.clr >> 16) & 0xff) / 255);
		tmp.y = dot(l, n) * ((float)((lgt.clr >> 8) & 0xff) / 255);
		tmp.z = dot(l, n) * ((float)(lgt.clr & 0xff) / 255);
		n = n * dot(n, l) * 2 - l;
		l = cam.pnt - slt.pnt;
		add_if(c.k, tmp);
		if (dot(n, l) / (length(l) *
			length(n)) > 0 && slt.dif > 0)
		{
			dif = pow(dot(n, l) / (length(l) *
				length(n)), slt.dif);
			c.sm_clr->x += ((float)((lgt.clr >> 16) & 0xff) / 255) * dif;
			c.sm_clr->y += ((float)((lgt.clr >> 8) & 0xff) / 255) * dif;
			c.sm_clr->z += ((float)(lgt.clr & 0xff) / 255) * dif;
		}
	}
}

int		calculate_clr(t_obj slt, const t_cam cam, __global const t_obj *obj, const int num_obj)
{
	float3		k;
	float3		sm_clr;
	float3		rgb;
	t_cal_clr	c;
	int			i;

	i = 0;
	k = 0;
	sm_clr = 0;
	c.k = &k;
	c.sm_clr = &sm_clr;
	while (i < (int)num_obj)
	{
		if (obj[i].type == LIGHT)
			for_every_light(slt, obj[i], c, cam, obj, num_obj);
		i++;
	}
	k = compare(k, 1);
	rgb.x = ((slt.clr >> 16) & 0xff) * k.x + 255 * sm_clr.x;
	rgb.y = ((slt.clr >> 8) & 0xff) * k.y + 255 * sm_clr.y;
	rgb.z = (slt.clr & 0xff) * k.z + 255 * sm_clr.z;
	rgb = compare(rgb, 255);
	return ((((int)rgb.x & 0xff) << 16) | (((int)rgb.y &
		0xff) << 8) | ((int)rgb.z & 0xff));
}
