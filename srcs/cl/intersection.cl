// #include "world.h"
// #include "cl_rt.h"

bool	bbox_intersection(t_ray ray, t_bbox bbox)
{
	// float tmin = (bbox.min.x - ray.origin.x) / ray.direction.x;
	// float tmax = (bbox.max.x - ray.origin.x) / ray.direction.x;

	// if (tmin > tmax) swap(&tmin, &tmax);

	// float tymin = (bbox.min.y - ray.origin.y) / ray.direction.y;
	// float tymax = (bbox.max.y - ray.origin.y) / ray.direction.y;

	// if (tymin > tymax) swap(&tymin, &tymax);

	// if ((tmin > tymax) || (tymin > tmax))
	// 	return false;

	// if (tymin > tmin)
	// 	tmin = tymin;

	// if (tymax < tmax)
	// 	tmax = tymax;

	// float tzmin = (bbox.min.z - ray.origin.z) / ray.direction.z;
    // float tzmax = (bbox.max.z - ray.origin.z) / ray.direction.z;

    // if (tzmin > tzmax) swap(&tzmin, &tzmax);

    // if ((tmin > tzmax) || (tzmin > tmax))
    //     return false;

    // if (tzmin > tmin)
    //     tmin = tzmin;

    // if (tzmax < tmax)
    //     tmax = tzmax;

    // return true;

	float ox = ray.origin.x;
	float oy = ray.origin.y;
	float oz = ray.origin.z;
	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	float a = 1.0f / dx;

	if (a >= 0.0f)
	{
		tx_min = (bbox.min.x - ox) * a;
		tx_max = (bbox.max.x - ox) * a;
	}
	else
	{
		tx_min = (bbox.max.x - ox) * a;
		tx_max = (bbox.min.x - ox) * a;
	}
	float b = 1.0f / dy;
	if (b >= 0.0f)
	{
		ty_min = (bbox.min.y - oy) * b;
		ty_max = (bbox.max.y - oy) * b;
	}
	else
	{
		ty_min = (bbox.max.y - oy) * b;
		ty_max = (bbox.min.y - oy) * b;
	}

	float c = 1.0f / dz;
	if (c >= 0.0f)
	{
		tz_min = (bbox.min.z - oz) * c;
		tz_max = (bbox.max.z - oz) * c;
	}
	else
	{
		tz_min = (bbox.max.z - oz) * c;
		tz_max = (bbox.min.z - oz) * c;
	}
	float t0, t1;
	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;
	if (tz_max < t1)
		t1 = tz_max;

	return (t0 < t1 && t1 > 0.0f);
}

/* NOTE: we can just return true and tmin
** because we check intersection with aabb
*/
bool	box_intersection(t_ray ray, t_obj box, t_shade_rec *const shade_rec,
						float *const tmin)
{
	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;
	float a = 1.0f / ray.direction.x;
	float b = 1.0f / ray.direction.y;
	float c = 1.0f / ray.direction.z;

	// t_bbox bbox = box.bounding_box;
	t_bbox bbox;
	bbox.min = box.direction;
	bbox.max = box.dir2;

	if (a >= 0.0f)
	{
		tx_min = (bbox.min.x - ray.origin.x) * a;
		tx_max = (bbox.max.x - ray.origin.x) * a;
	}
	else
	{
		tx_min = (bbox.max.x - ray.origin.x) * a;
		tx_max = (bbox.min.x - ray.origin.x) * a;
	}
	if (b >= 0.0f)
	{
		ty_min = (bbox.min.y - ray.origin.y) * b;
		ty_max = (bbox.max.y - ray.origin.y) * b;
	}
	else
	{
		ty_min = (bbox.max.y - ray.origin.y) * b;
		ty_max = (bbox.min.y - ray.origin.y) * b;
	}
	if (c >= 0.0f)
	{
		tz_min = (bbox.min.z - ray.origin.z) * c;
		tz_max = (bbox.max.z - ray.origin.z) * c;
	}
	else
	{
		tz_min = (bbox.max.z - ray.origin.z) * c;
		tz_max = (bbox.min.z - ray.origin.z) * c;
	}

	float	t0, t1;
	float4 norm_in, norm_out;
	if (tx_min > ty_min)
	{
		t0 = tx_min;
		norm_in = (a >= 0.0f) ? (float4)(-1.0f, 0.0f, 0.0f, 0.0f)
							  : (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		t0 = ty_min;
		norm_in = (b >= 0.0f) ? (float4)(0.0f, -1.0f, 0.0f, 0.0f)
							  : (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	}
	if (tz_min > t0)
	{
		t0 = tz_min;
		norm_in = (c >= 0.0f) ? (float4)(0.0f, 0.0f, -1.0f, 0.0f)
							  : (float4)(0.0f, 0.0f, 1.0f, 0.0f);
	}

	if (tx_max < ty_max)
	{
		t1 = tx_max;
		norm_out = (a > 0.0f) ? (float4)(1.0f, 0.0f, 0.0f, 0.0f)
							  : (float4)(-1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		t1 = ty_max;
		norm_out = (b > 0.0f) ? (float4)(0.0f, 1.0f, 0.0f, 0.0f)
							  : (float4)(0.0f, -1.0f, 0.0f, 0.0f);
	}
	if (tz_max < t1)
	{
		t1 = tz_max;
		norm_out = (c > 0.0f) ? (float4)(0.0f, 0.0f, 1.0f, 0.0f)
							  : (float4)(0.0f, 0.0f, -1.0f, 0.0f);
	}

	if (t0 < t1 && t1 > EPSILON)
	{
		if (t0 > EPSILON && t0 < *tmin)
		{
			*tmin = t0;
			shade_rec->local_hit_point = ray.direction * t0 + ray.origin;
			shade_rec->normal = norm_in;
			return (true);
		}
		else if (t1 < *tmin)
		{
			*tmin = t1;
			shade_rec->local_hit_point = ray.direction * t1 + ray.origin;
			shade_rec->normal = norm_out;
			return (true);
		}
	}
	return (false);
}

inline bool	generic_sphere_instersection(t_ray ray, t_obj sphere,
										t_shade_rec *const shade_rec,
										float *const tmin)
{
	float a = dot(ray.direction, ray.direction);
	float b = 2.0f * dot(ray.direction, ray.origin);
	float c = dot(ray.origin, ray.origin) - 1.0f;
	c = b * b - 4.0f * a * c; // DISC = (b/2)^2-ac

	if (c < 0.0f)
		return (false);
	c = sqrt(c);
	float t = (-b - c) / (2.0f * a);
	if (t > 0.0f && t < *tmin)
	{
		shade_rec->local_hit_point = ray.direction * t + ray.origin;
		// float phi = atan2(shade_rec->local_hit_point.x,
						// shade_rec->local_hit_point.z);
		// if (phi < 0.0f)
			// phi += M_PI * 2.0f;
		// if (phi >= 0.0f && phi <= M_PI / 2)
		// {
			shade_rec->normal = get_sphere_normal(shade_rec->local_hit_point,
												sphere);
			*tmin = t;
			return (true);
		// }
	}

	/* second root */
	t = (-b + c) / (2.0f * a);

	if (t > 0.0f && t < *tmin)
	{
		shade_rec->local_hit_point = ray.direction * t + ray.origin;
		// float phi = atan2(shade_rec->local_hit_point.x,
						// shade_rec->local_hit_point.z);
		// if (phi < 0.0f)
			// phi += M_PI * 2.0f;
		// if (phi >= 0.0f && phi <= M_PI / 2)
		// {
			shade_rec->normal = get_sphere_normal(shade_rec->local_hit_point,
												sphere);
			*tmin = t;
			return (true);
		// }
	}

	return (false);
}

bool	generic_plane_intersection(t_ray ray, float *const tmin,
									t_shade_rec *const shade_rec)
{
	bool	ret = false;
	float	denom = ray.direction.y;
	float	t;

//    t = -X|V / D|V

// 	t = -dot(object.origin - ray.origin, (0, 1, 0, 0)) / dot(ray.direction, plane.direction);
// 	t = -dot(-ray.origin, (0, 1, 0, 0)) / dot(ray.direction, plane.direction);
// 	t = ray.origin.y / ray.direction.y

	if (denom != 0.0f)
	{
		t = -ray.origin.y;
		if (t * denom > 0.0f)
		{
			t = t / denom;
			if (t >= EPSILON && t < *tmin)
			{
				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
				ret = true;
			}
		}
	}
	return (ret);
}

bool	disk_intersection(t_ray ray, t_obj disk, t_shade_rec *const shade_rec,
							float *const tmin)
{
	float4	a;
	float	t;
	float	denom;
	bool	ret;

	ret = false;
	denom = dot(ray.direction, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	if (denom != 0)
	{
		a = disk.origin - ray.origin;
		t = dot(a, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
		if (t * denom > 0.0f) //different signes
		{
			t = t / denom;
			if (t >= EPSILON && t < *tmin)
			{
				float4 point = t * ray.direction + ray.origin;
				if (dot(point - disk.origin, point - disk.origin) < disk.r2)
				{
					*tmin = t;
					shade_rec->local_hit_point = point;
					shade_rec->normal = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
					ret = true;
				}
			}
		}
	}
	return (ret);
}

bool	rectangle_intersection(t_ray ray, t_obj rectangle,
							t_shade_rec *const shade_rec,
							float *const tmin)
{

	bool	ret = false;
	float	denom = ray.direction.y;
	float	t;

	if (denom != 0.0f)
	{
		t = -ray.origin.y;
		if (t * denom > 0.0f)
		{
			t = t / denom;
			if (t >= EPSILON && t < *tmin)
			{
				float4	d = ray.direction * t + ray.origin;

				float ddota = d.x;
				if (ddota < 0.0f || ddota > rectangle.r)
					return (false);

				float ddotb = d.z;
				if (ddotb < 0.0f || ddotb > rectangle.r2)
					return (false);

				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
				ret = true;
			}
		}
	}
	return (ret);

	// return (ret);
	// float4	d;
	// float	t;
	// float	denom;

	// denom = ray.direction.z;
	// d = -ray.origin;
	// t = -ray.origin.z;
	// t = t / denom;
	// if (t * denom > 0.0f)
	// {
	// 	if (t >= 0.0f && t < *tmin)
	// 	{
	// 		float4 point =  t * ray.direction + ray.origin;
	// 		d = point;

	// 		float ddota = dot(d, (cl_float4)(1.0f, 0.0f, 0.0f, 0.0f));
	// 		if (ddota < 0.0f || ddota > rectangle.r * rectangle.r)
	// 			return (false);

	// 		float ddotb = dot(d, (cl_float4)(0.0f, 1.0f, 0.0f, 0.0f));
	// 		if (ddotb < 0.0f || ddotb > rectangle.r2 * rectangle.r2)
	// 			return (false);

	// 		*tmin = t;
	// 		shade_rec->local_hit_point = d;
	// 		shade_rec->normal = (float4)(0.0f, 0.0f, 1.0f, 0.0f);
	// 		return (true);
	// 	}
	// }
	// return (false);
}

/*
** TODO(dmelessa): cap cylinder with discs
*/
 bool cylinder_intersection(t_ray ray, t_obj cylinder, t_shade_rec *shade_rec, float *const tmin)
{
	float	a, b, c, disc;

	a = dot(ray.direction, ray.direction) - ray.direction.y * ray.direction.y;
	b = 2.0f * (dot(ray.direction, ray.origin) - ray.direction.y * ray.origin.y);
	c = dot(ray.origin, ray.origin) - ray.origin.y * ray.origin.y - 1.0f;
	disc = b * b - 4.0f * a * c;

	if (disc >= 0.0f)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		float t = (-b - disc) / a;
		if (cylinder.maxm > 0.0f)
		{
			float m = ray.direction.y * t + ray.origin.y;
			if (t > 0.0f && t < *tmin && m < cylinder.maxm && m > 0.0f)
			{
				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = get_cylinder_normal(shade_rec->local_hit_point, cylinder, m);
				return true;
			}
			t = (-b + disc) / a;
			m = ray.direction.y * t + ray.origin.y;
			if (t > 0.0f && t < *tmin && m > 0.0f && m < cylinder.maxm)
			{
				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = get_cylinder_normal(shade_rec->local_hit_point, cylinder, m);
				return true;
			}
		}
	}
	return false;
}

/*
** TODO(dmelessa): cap cone with disc
*/
 bool	cone_intersection(t_ray ray, t_obj cone, float *const tmin,
 						t_shade_rec *const shade_rec)
{
	float4	x;
	float	dv, xv, a, b, c, disc;

	x = ray.origin;
	dv = ray.direction.y;
	xv = ray.origin.y;
	a = dot(ray.direction, ray.direction) - cone.r2 * dv * dv;
	b = 2.0f * (dot(ray.direction, x) - cone.r2 * dv * xv);
	c = dot(x, x) - cone.r2 * xv * xv;
	disc = b * b - 4.0f * a * c;

	if (disc >= 0.0f)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		float	t = (-b - disc) / a;
		if (t > 0.0f && t < *tmin)
		{
			float	m = ray.direction.y * t + ray.origin.y;
			if (m >= cone.minm && m <= cone.maxm)
			{
				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = get_cone_normal(shade_rec->local_hit_point,
													cone, m);
				return (true);
			}
		}

		t = (-b + disc) / a;
		if (t > 0.0f && t < *tmin)
		{
			float	m = ray.direction.y * t + ray.origin.y;
			if (m >= cone.minm && m <= cone.maxm)
			{
				*tmin = t;
				shade_rec->local_hit_point = ray.direction * t + ray.origin;
				shade_rec->normal = get_cone_normal(shade_rec->local_hit_point,
													cone, m);
				return (true);
			}
		}
	}
	return (false);
}

 bool	paraboloid_intersection(t_ray ray, t_obj paraboloid,
 							t_shade_rec *const shade_rec, float *const tmin)
{
	float4	x;
	float	a, b, c, dv, xv, disc;
	bool ret = false;

	x = ray.origin;
	dv = dot(ray.direction, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	xv = dot(x, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
	a = dot(ray.direction, ray.direction) - dv * dv;
	b = 2.0f * (dot(ray.direction, x) - dv * (xv + 2.0f * paraboloid.r));
	c = dot(x, x) - xv * (xv + 4.0f * paraboloid.r);
	disc = b * b - 4.0f * a * c;
	if (disc > 0.0f)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		float	t = (-b - disc) / a;
		if (t > 0.0f && t < *tmin)
		{
			shade_rec->local_hit_point = ray.direction * t + ray.origin;
			float	m = dot(shade_rec->local_hit_point, (float4)(0.0f, 1.0f, 0.0f, 0.0f));

			if (m > 0.0f && m < paraboloid.maxm)
			{
				*tmin = t;
				shade_rec->normal = get_paraboloid_normal(shade_rec->local_hit_point, paraboloid, m);
				ret = true;
			}
		}

		t = (-b + disc) / a;
		if (t > 0.0f && t < *tmin)
		{
			shade_rec->local_hit_point = ray.direction * t + ray.origin;
			float	m = dot(shade_rec->local_hit_point, (float4)(0.0f, 1.0f, 0.0f, 0.0f));
			// float	m = ray.direction.y * t + ray.origin.y;
			if (m > 0.0f && m < paraboloid.maxm)
			{
				*tmin = t;
				shade_rec->normal = get_paraboloid_normal(shade_rec->local_hit_point, paraboloid, m);
				ret = true;
			}
		}
	}
	return (ret);
}

 bool	torus_intersecion(t_ray ray, t_obj torus, t_shade_rec *shade_rec, float *const tmin)
{
	double	coeffs[5];
	double	roots[4];
	float	m, n, o, r2, R2;
	int		num_real_roots;

	m = dot(ray.direction, ray.direction);
	n = dot(ray.direction, ray.origin);
	o = dot(ray.origin, ray.origin);
	r2 = torus.r2 * torus.r2;
	R2 = torus.r * torus.r;

	coeffs[4] = m * m; //a
	coeffs[3] = 4.0f * n * m; //b
	coeffs[2] = 4.0f * n * n + 2.0f * m * o - 2.0f * (R2 + r2) * m + 4.0f * R2 * ray.direction.y * ray.direction.y;
	coeffs[1] = 4.0f * n * o - 4.0f * (R2 + r2) * n + 8.0f * R2 * ray.direction.y * ray.origin.y;
	coeffs[0] = o * o - 2.0f * (R2 + r2) * o + 4.0f * R2 * ray.origin.y * ray.origin.y + (R2 - r2) * (R2 - r2);
	num_real_roots = SolveQuartic(coeffs, roots);
	bool	intersect = false;

	if (num_real_roots == 0)
		return false;

	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > EPSILON && roots[j] < *tmin)
		{
			intersect = true;
			*tmin = roots[j];
			shade_rec->local_hit_point = ray.direction * *tmin + ray.origin;
			shade_rec->normal = get_torus_normal(shade_rec->local_hit_point, torus);
			*tmin = *tmin * 0.99f;
		}
	}
	// hit_info->t = t * 0.99f;
	return (intersect);
}

float4	mobius_normal(t_obj mobius, float4 point)
{
	float x = point.x, y = point.y, z = point.z, R = mobius.r;

	float4 norm = (float4)(2 * x * y - 2 * R * z - 4 * x * z,
							-R * R + x * x + 3 * y * y - 4 * y * z + z * z,
							-2 * R * x - 2 * x * x - 2 * y * y + 2 * y * z,
							0.0f);

	return normalize(norm);
}

int dblsgn(double x) {
		return (x < -1e-4f) ? (-1) : (x > 1e-4f);
}

bool	mobius_intersection(t_ray ray, t_obj mobius, t_shade_rec *shade_rec, float *const tmin)
{
	float ox = ray.origin.x;
	float oy = ray.origin.y;
	float oz = ray.origin.z;
	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;
	float R = mobius.r;

	double	coefs[4];
	double	roots[3];


	coefs[3] = 1.0f;
	coefs[2] = -2.0f * oz;
	coefs[1] = -R * R + ox * ox + oz * oz;
	coefs[0] = -2.0f * R* ox * oz -2.0f * ox * ox * oz;
	// coefs[0] = 1.0f;
	// coefs[1] = -2.0f * oz;
	// coefs[2] = ox * ox + oz * oz - R * R;
	// coefs[3] = 2 * ox * oz * (ox + R);

	// coefs[0] = ox * ox * oy + oy * oy * oy - 2.0f * ox * ox * oz - 2.0f * oy * oy * oz +
	// 		oy * oz * oz - 2.0f * ox * oz * R - oy * R * R;
	// coefs[1] = dy * ox * ox - 2.0f * dz * ox * ox + 2.0f * dx * ox * oy + 3.0 * dy * oy * oy -
	// 		2.0f * dz * oy * oy - 4.0f * dx * ox * oz - 4.0f * dy * oy * oz + 2.0f * dz * oy * oz +
	// 		dy * oz * oz - 2.0f * dz * ox * R - 2.0f * dx * oz * R - dy * R * R;
	// coefs[2] = 2.0f * dx * dy * ox - 4.0f * dx * dz * ox + dx * dx * oy + 3.0 * dy * dy * oy -
	// 		4.0f * dy * dz * oy + dz * dz * oy - 2.0f * dx * dx * oz - 2.0f * dy * dy * oz +
	// 		2.0f * dy * dz * oz - 2.0f * dx * dz * R;
	// coefs[3] = dx * dx * dy + dy * dy * dy - 2.0f * dx * dx * dz - 2.0f * dy * dy * dz +
	// 		dy * dz * dz;
	int num = SolveCubic(coefs, roots);

	bool ret = false;

	for (int i = 0; i < num; i++)
	{
		if (roots[i] > 0.0f && roots[i] < *tmin)
		{
			float4 pt = ray.origin + ray.direction * (float)roots[i];
			float x = pt.x, y = pt.y, z = pt.z;
			float t = atan2(y, x), s;

			if (dblsgn(sin(t / 2)) != 0) {
				s = z / sin(t / 2.0f);
			} else {
				if (dblsgn(cos(t)) != 0) {
					s = (x / cos(t) - R) / cos(t / 2.0f);
				} else {
					s = (y / sin(t) - R) / cos(t / 2.0f);
				}
			}

			x -= (R + s * cos(t / 2.0f)) * cos(t);
			y -= (R + s * cos(t / 2.0f)) * sin(t);
			z -= s * sin(t / 2.0f);

			if (!((x * x + y * y + z * z) <= 1e-3f &&
				(x * x + y * y + z * z) >= -1e-3f)) {
				continue ;
			}

			//half_width
			if (s >= -0.5f -EPSILON  && s <= 0.5f + EPSILON /* && t > 0.0f && t < M_PI_F * 2.0f */)
			{
				shade_rec->local_hit_point = pt;
				shade_rec->normal = mobius_normal(mobius, pt);
				*tmin = roots[i];
				ret = true;
			}
		}
	}
	return (ret);
}

/*
** TODO(dmelessa): change later
*/
bool	triangle_intersection(t_ray ray, t_triangle triangle,
								t_shade_rec *const shade_rec,
								float *const tmin)
{
	float4	pvec = cross(ray.direction, triangle.vector2);
	float	det = dot(triangle.vector1, pvec);
	float	t;

	if (det < 1e-8 && det > -1e-8)
		return false;

	float	inv_det = 1.0f / det;
	float4	tvec = ray.origin - triangle.vertex1;
	float	u = dot(tvec, pvec) * inv_det;
	if (u < EPSILON || u > 1)
		return false;

	float4	qvec = cross(tvec, triangle.vector1);
	float	v = dot(ray.direction, qvec) * inv_det;
	if (v < EPSILON || u + v > 1)
		return false;
	t = dot(triangle.vector2, qvec) * inv_det;
	if (t > EPSILON && t < *tmin)
	{
		*tmin = t;
		shade_rec->local_hit_point = ray.direction * t + ray.origin;
		shade_rec->normal = cross(triangle.vector1, triangle.vector2);
		return true;
	}
	return false;
}

bool
is_intersect(t_obj const obj, t_type const type, t_ray const ray,
			t_shade_rec *const shade_rec, float *const tmin)
{
	if (type == sphere)
	{
		return (generic_sphere_instersection(ray, obj, shade_rec, tmin));
	}
	else if (type == plane)
	{
		return (generic_plane_intersection(ray, tmin, shade_rec));
	}
	else if (type == cylinder)
	{
		return cylinder_intersection(ray, obj, shade_rec, tmin);
	}
	else if (type == cone)
	{
		return (cone_intersection(ray, obj, tmin, shade_rec));
	}
	else if (type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, shade_rec, tmin));
	}
	else if (type == torus)
	{
		return torus_intersecion(ray, obj, shade_rec, tmin);
	}
	else if (type == box)
	{
		return box_intersection(ray, obj, shade_rec, tmin);
	}
	else if (type == disk)
	{
		return (disk_intersection(ray, obj, shade_rec, tmin));
	}
	else if (type == rectangle)
	{
		return (rectangle_intersection(ray, obj, shade_rec, tmin));
	}
	// else if (type == mobius)
	// {
		// return (mobius_intersection(ray, obj, shade_rec, tmin));
	// }
	return (false);
}

t_ray	transform_ray(t_ray ray, t_matrix transformation_matrix)
{
	t_ray	inv_ray;

	inv_ray.direction = vector_matrix_mul(ray.direction, transformation_matrix);
	inv_ray.origin = point_matrix_mul(ray.origin, transformation_matrix);
	return (inv_ray);
}

bool	instance_hit(t_instance_manager instance_mngr,
					t_instance instance,
					float *const tmin,
					t_shade_rec *shade_rec)
{
	bool		intersect = false;
	t_matrix	matrix = get_instance_matrix(instance_mngr, instance);
	t_ray		ray = transform_ray(shade_rec->ray, matrix);

	if (instance.type == triangle)
	{
		intersect = (triangle_intersection(ray,
										instance_mngr.triangles[instance.object_id],
										shade_rec, tmin));
	}
	else
	{
		t_obj		object = instance_mngr.objects[instance.object_id];
		intersect = (is_intersect(object, instance.type, ray,
								shade_rec,tmin));
	}

	if (intersect)
	{
		shade_rec->normal = normalize(transform_normal(shade_rec->normal,
														matrix));
	}
	return (intersect);
}
