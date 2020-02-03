
t_obj	circle(t_cam ray, t_obj obj)
{
	t_obj	slt;
	float3	d;
	float3	p_c;
	float	t;

	slt = new_obj(ray.pnt, 0, 0, obj.clr, 0, 0);
	t = (dot(obj.pnt, obj.dir) - dot(ray.pnt, obj.dir)) / dot(ray.dir, obj.dir);
	if (dot(ray.dir, obj.dir) == 0 || t <= 0.00001)
		return (slt);
	p_c = ray.dir * t + ray.pnt - obj.pnt;
	if (dot(p_c, p_c) > pow(obj.r, 2))
		return (slt);
	d = (dot(ray.dir, obj.dir) < dot(ray.dir, -1 *obj.dir)) ? obj.dir : (-1 * obj.dir);
	slt.dir = d;
	slt.pnt = ray.pnt + ray.dir * t;
	slt.dif = obj.dif;
	slt.ref = obj.ref;
	return (slt);
}

float3	cone_abc(t_cam ray, t_obj cne, float3 mn)
{
	float3	abc;

	abc.x = dot(ray.dir - cne.dir * mn.x, ray.dir - cne.dir * mn.x) - pow(cne.r * mn.x, 2);
	abc.y = 2 * dot(ray.dir - cne.dir * mn.x, ray.pnt - cne.dir * mn.y - cne.pnt) - 2 * mn.x * mn.y * pow(cne.r, 2);
	abc.z = dot(ray.pnt - cne.dir * mn.y - cne.pnt, ray.pnt - cne.dir * mn.y - cne.pnt) - pow(cne.r * mn.y, 2);
	return (abc);
}

float3	cone_cylinder_mn(t_cam ray, t_obj cne)
{
	float3	mn;

	mn.x = dot(ray.dir, cne.dir) / dot(cne.dir, cne.dir);
	mn.y = dot(ray.pnt - cne.pnt, cne.dir) / dot(cne.dir, cne.dir);
	return (mn);
}

t_obj	cone(t_cam ray, t_obj cne)
{
	t_obj	slt;
	float3	mn;
	float3	abc;
	float3	dt;

	slt = new_obj(ray.pnt, 0, 0, cne.clr, 0, 0);
	mn = cone_cylinder_mn(ray, cne);
	abc = cone_abc(ray, cne, mn);
	dt.z = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (dt.z < 0)
		return (slt);
	dt = discriminant(abc.x, abc.y, dt.z);
	if (dt.z <= 0.00001 || dt.z * mn.x + mn.y < 0)
		return (slt);
	slt.pnt = ray.pnt + ray.dir * dt.z;
	abc = ray.dir * dt.z +(ray.pnt - cne.pnt);
	dt.x = dot(abc, abc) / dot(cne.dir, abc);
	slt.dir = slt.pnt - (cne.pnt + cne.dir * dt.x);
	if (dt.z * mn.x + mn.y > 1)
		slt = circle(ray, new_obj(cne.pnt + cne.dir, cne.dir, cne.r, cne.clr, cne.dif, cne.ref));
	slt.dif = cne.dif;
	slt.ref = cne.ref;
	return (slt);
}

float3	cylinder_abc(t_cam ray, t_obj cld, float3 mn)
{
	float3	abc;

	abc.x = dot(ray.dir - cld.dir * mn.x, ray.dir - cld.dir * mn.x);
	abc.y = 2 * dot(ray.dir - cld.dir * mn.x, ray.pnt - cld.dir * mn.y - cld.pnt);
	abc.z = dot(ray.pnt - cld.dir * mn.y - cld.pnt, ray.pnt - cld.dir * mn.y - cld.pnt) - pow(cld.r, 2);
	return (abc);
}

t_obj	cylinder(t_cam ray, t_obj cld)
{
	t_obj	slt;
	float3	mn;
	float3	abc;
	float3	dt;

	slt = new_obj(ray.pnt, 0, 0, cld.clr, 0, 0);
	mn = cone_cylinder_mn(ray, cld);
	abc = cylinder_abc(ray, cld, mn);
	dt.z = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (dt.z < 0)
		return (slt);
	dt = discriminant(abc.x, abc.y, dt.z);
	if (dt.z <= 0.00001)
		return (slt);
	slt.pnt = ray.pnt + ray.dir * dt.z;
	slt.dir = slt.pnt - (cld.pnt + cld.dir * (dt.z * mn.x + mn.y));
	if (dt.z * mn.x + mn.y > 1)
		slt = circle(ray, new_obj(cld.pnt + cld.dir, cld.dir, cld.r, cld.clr, cld.dif, cld.ref));
	if (dt.z * mn.x + mn.y < 0)
		slt = circle(ray, new_obj(cld.pnt, cld.dir, cld.r, cld.clr, cld.dif, cld.ref));
	slt.dif = cld.dif;
	slt.ref = cld.ref;
	return (slt);
}

t_obj	plane(t_cam ray, t_obj pln)
{
	t_obj	slt;
	float	t;
	float3	d;

	slt = new_obj(ray.pnt, 0, 0, pln.clr, 0, 0);
	t = (dot(pln.pnt, pln.dir) - dot(ray.pnt, pln.dir)) /
		dot(ray.dir, pln.dir);
	if (dot(ray.dir, pln.dir) == 0 || t <= 0.00001)
		return (slt);
	d = (dot(ray.dir, pln.dir) < dot(ray.dir, (-1 * pln.dir))) ?
		pln.dir : (-1 * pln.dir);
	slt.dir = d;
	slt.pnt = ray.pnt + ray.dir * t;
	slt.dif = pln.dif;
	slt.ref = pln.ref;
	return (slt);
}

t_obj	sphere(t_cam ray, t_obj sph)
{
	t_obj	slt;
	float3	abc;
	float3	dt;
	float3	p0_c;

	slt = new_obj(ray.pnt, 0, 0, sph.clr, 0, 0);
	p0_c = ray.pnt - sph.pnt;
	abc.x = dot(ray.dir, ray.dir);
	abc.y = 2 * dot(ray.dir, p0_c);
	abc.z = dot(p0_c, p0_c) - pow(sph.r, 2);
	dt.z = pow(abc.y, 2) - 4 * abc.x * abc.z;
	if (dt.z < 0)
		return (slt);
	dt = discriminant(abc.x, abc.y, dt.z);
	if (dt.z <= 0.00001)
		return (slt);
	slt.pnt = ray.pnt + ray.dir * dt.z;
	slt.dir = slt.pnt - sph.pnt;
	slt.dif = sph.dif;
	slt.ref = sph.ref;
	return (slt);
}
