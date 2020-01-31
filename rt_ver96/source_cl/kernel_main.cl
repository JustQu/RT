
int		fresh_color(int n, int m, float ref)
{
	int3	r;
	float3	n1;
	float3	m1;

	n1.x = (n >> 16) & 0xff;
	n1.y = (n >> 8) & 0xff;
	n1.z = n & 0xff;
	m1.x = (m >> 16) & 0xff;
	m1.y = (m >> 8) & 0xff;
	m1.z = m & 0xff;
	if (ref > 1)
		ref = 1;
	r.x = (int)(n1.x * (1 - ref) + m1.x * ref) & 0xff;
	r.y = (int)(n1.y * (1 - ref) + m1.y * ref) & 0xff;
	r.z = (int)(n1.z * (1 - ref) + m1.z * ref) & 0xff;
	return (((r.x & 0xff) << 16) | ((r.y & 0xff) << 8) | (r.z & 0xff));
}

t_obj			closest_figure(t_cam ray, __global const t_obj *obj, const int n)
{
	t_obj	slt;
	t_obj	tmp;
	float	s;
	float	t;
	int		i;

	i = 0;
	slt = new_obj(ray.pnt, 0, 0, 0, 0, 0);
	while (i < n)
	{
		if (obj[i].type == CONE)
			tmp = cone(ray, obj[i]);
		else if (obj[i].type == CYLINDER)
			tmp = cylinder(ray, obj[i]);
		else if (obj[i].type == CIRCLE)
			tmp = circle(ray, obj[i]);
		else if (obj[i].type == PLANE)
			tmp = plane(ray, obj[i]);
		else if (obj[i].type == SPHERE)
			tmp = sphere(ray, obj[i]);
		else
		{
			i++;
			continue;
		}
		s = distance(slt.pnt, ray.pnt);
		t = distance(tmp.pnt, ray.pnt);
		if (!(tmp.dir.x == 0 && tmp.dir.y == 0 && tmp.dir.z == 0) && (s == 0 || (s > t && t != 0)))
			slt = tmp;
		i++;
	}
	return (slt);
}

int				get_color(t_cam ray, const t_cam cam, __global const t_obj *obj, const int n)
{
	t_obj	slt;
	int		clr;
	int		mclr[REFLECTIONS + 1];
	float	mref[REFLECTIONS + 1];
	int		i;

	i = 0;
	clr = 0;
	while (i <= REFLECTIONS)
	{
		slt = closest_figure(ray, obj, n);
		if (slt.dir.x == 0 && slt.dir.y == 0 && slt.dir.z == 0)
			break ;
		mclr[i] = calculate_clr(slt, cam, obj, n);
		mref[i] = slt.ref;
		ray.pnt = slt.pnt;
		ray.dir = ray.dir - slt.dir * 2 * dot(slt.dir, ray.dir);
		i++;
		if (slt.ref <= 0)
			break ;
	}
	while (i > 0)
	{
		clr = fresh_color(mclr[i - 1], clr, mref[i - 1]);
		i--;
	}
	return(clr);
}

__kernel void	kernel_main(__global int *img, const t_cam cam, __global const t_obj *obj, const int num_obj)
{
    int		gl_id = get_global_id(0);
	int		x = -1 * WIN_W / 2 + gl_id % WIN_W; 
	int		y = -1 * WIN_H / 2 + gl_id / WIN_W;
	t_cam	ray;
	float3	m;
	float3	n;
	float	k;
	float	l;

	k = pow(cam.dir.y, 2) + pow(cam.dir.x, 2);
	l = pow(cam.dir.x, 2) + pow(cam.dir.y, 2) + pow(cam.dir.z, 2);
	m.x = (-1) * cam.dir.y / sqrt(k);
	m.y = cam.dir.x / sqrt(k);
	m.z = 0;
	n.z = -1 * sqrt(k / l);
	n.x = n.z * ((-1) * cam.dir.z * cam.dir.x) / k;
	n.y = n.z * ((-1) * cam.dir.z * cam.dir.y) / k;
	m = normalize(m);
	n = normalize(n);
	ray.dir = cam.dir + (m * 4 * x) / WIN_W + (n * 4 * y) / WIN_W;
	ray.pnt = cam.pnt;
	img[gl_id] = get_color(ray, cam, obj, num_obj);
}
