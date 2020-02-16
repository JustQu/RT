#include "world.h"
#include "solver.cl"

struct	s_ray
{
	float4	origin;
	float4	direction;
};
typedef struct s_ray	t_ray;

t_ray	cast_primal_ray(t_camera camera, int x, int y)
{
	t_ray	ray;
	float	px;
	float	py;

	px = (2 * ((x + 0.5f) / DEFAULT_WIDTH) - 1) * camera.angle * camera.ratio;
	py = (1 - 2 * (y + 0.5f) / DEFAULT_HEIGHT) * camera.angle;
	ray.origin = camera.origin;
	ray.direction = (float4)(px, py, 1.0f, 0.0f);//need to rotate vector if we have rotated camera
	ray.direction = normalize(ray.direction);
	return ray;
}

bool	sphere_intersection(t_ray ray, t_obj sphere, float *tr)
{
#if 1 // geometric solution

	float4 L = sphere.origin - ray.origin;
	float tca = dot(L, ray.direction);
	if (tca < 0.0f)
		return false;
	float d2 = dot(L, L) - tca * tca;
	if (d2 > sphere.r2) //r^2 should be precomputed
		return false;
	float thc = sqrt(sphere.r2 - d2);
	float t = tca - thc;
	if (t < 0.0f)
	{
		t = tca + thc;
		if (t < 0.0f)
			return false;
	}
	*tr = t;
	return true;

#elif 1// analytic solution

	float4 L = sphere.origin - ray.origin;
	float a = 1; //NOTE: if ray.direction normalized!
	float b = dot(ray.direction, L); //b/2
	float c = dot(L, L) - sphere.r2;
	float disc = b * b - c; // DISC = (b/2)^2-ac

	if (disc < 0.0f)
		return false;
	a = sqrt(disc);
	*tr = b - a;
	if (*tr < 0.0f)
	{
		*tr = b + a;
		if (*tr < 0.0f)
			return false;
	}
	return true;
#endif
}

/**
** there could be mistake
** need some tests
*/
bool	plane_intersection(t_ray ray, t_obj plane, float *tr)
{
	float4	a;
	float	t;
	float	denom;

	denom = dot(plane.direction, ray.direction);
	if (denom != 0)
	{
		a = plane.origin - ray.origin;
		t = dot(a, plane.direction);
		if (t * denom < 0) //different signes
		{
			*tr = t / denom;
			return (*tr >= 0);
		}
		else
		{
			*tr = t / denom;
			return (*tr >= 0);
		}
		return false;
	}
	return (false);
}

/*
** TODO(dmelessa): cap cylinder with discs
*/
bool cylinder_intersection(t_ray ray, t_obj cylinder, float *tr)
{
	float4	x;
	float	a, b, c, dv, xv, disc;

	x = ray.origin - cylinder.origin;
	dv = dot(ray.direction, cylinder.direction);
	xv = dot(x, cylinder.direction);
	a = 1.0f - dv * dv; // 1 if ray direction is normalized else dot(d,d)
	b = 2.0f * (dot(ray.direction, x) - dv * xv);
	c = dot(x, x) - xv * xv - cylinder.r2;
	disc = b * b - 4.0f * a * c;
	if (disc >= 0.0f)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		*tr = (-b - disc) / a;
		if (*tr < 0.0f)
			*tr = (-b + disc) / a;
		if (*tr > 0.0f)
			if (cylinder.maxm > 0.0f)
			{
				float m1 = dv * *tr + xv;
				if (m1 < cylinder.maxm && m1 > 0.0f)
					return true;
			}
	}
	return false;
}

/*
** TODO(dmelessa): cap cone with disc
*/
bool	cone_intersection(t_ray ray, t_obj cone, float *tr)
{
	float4	x;
	float	dv, xv, a, b, c, disc;

	x = ray.origin - cone.origin;
	dv = dot(ray.direction, cone.direction);
	xv = dot(x, cone.direction);
	a = dot(ray.direction, ray.direction) - cone.r2 * dv * dv;
	b = 2.0f * (dot(ray.direction, x) - cone.r2 * dv * xv);
	c = dot(x, x) - cone.r2 * xv * xv;
	disc = b * b - 4 * a * c;
	if (disc >= 0.0f)
	{
		float m;
		a *= 2.0f;
		disc = sqrt(disc);
		*tr = (-b - disc) / a;
		if (*tr < 0.0f)
			*tr = (-b + disc) / a;
		if (*tr > 0.0f)
		{
			if (cone.maxm > 0.0f)
			{
				float m1 = dv * *tr + xv;
				if (m1 >= cone.minm && m1 <= cone.maxm)
					return true;
				*tr = (-b + disc) / a;
				m1 = dv * *tr + xv;
				if (m1 >= cone.minm && m1 <= cone.maxm)
					return true;
			}
			else
			{
				return (*tr >= 0.0f);
			}
		}
	}
	return (false);
}

bool	paraboloid_intersection(t_ray ray, t_obj paraboloid, float *tr)
{
	float4	x;
	float	a, b, c, dv, xv, disc;

	x = ray.origin - paraboloid.origin;
	dv = dot(ray.direction, paraboloid.direction);
	xv = dot(x, paraboloid.direction);
	a = 1.0f - dv * dv;
	b = 2.0f * (dot(ray.direction, x) - dv * (xv + 2.0f * paraboloid.r));
	c = dot(x, x) - xv * (xv + 4.0f * paraboloid.r);
	disc = b * b - 4.0f * a * c;
	if (disc >= 0.0f)
	{
		float m;
		a *= 2;
		disc = sqrt(disc);
		*tr = (-b - disc) / a;
		if (*tr < 0.0f)
			*tr = (-b + disc) / a;
		if (*tr > 0.0f)
		{
			if (paraboloid.maxm > 0.0f)
			{
				float m1 = dv * *tr + xv;
				if (m1 >= paraboloid.minm && m1 <= paraboloid.maxm)
					return true;
				*tr = (-b + disc) / a;
				m1 = dv * *tr + xv;
				if (m1 >= paraboloid.minm && m1 <= paraboloid.maxm)
					return true;
			}
			else
			{
				return (*tr >= 0.0f);
			}
		}
	}
	return (false);
}

bool	torus_intersecion(t_ray ray, t_obj torus, float *tr)
{
	double	coeffs[5];
	double	roots[4];
	float4	x;
	float	m, n, o, p, q, r2, R2;
	int		num_real_roots;

	x = ray.origin - torus.origin;
	m = dot(ray.direction, ray.direction);
	n = dot(ray.direction, x);
	o = dot(x, x);
	p = dot(ray.direction, torus.direction);
	q = dot(x, torus.direction);
	r2 = torus.r2 * torus.r2;
	R2 = torus.r * torus.r;

	coeffs[4] = m * m; //a
	coeffs[3] = 4.0f * n * m; //b
	coeffs[2] = 4.0f * n * n + 2.0f * m * o - 2.0f * (R2 + r2) * m + 4.0f * R2 * p * p;
	coeffs[1] = 4.0f * n * o - 4.0f * (R2 + r2) * n + 8.0f * R2 * p * q;
	coeffs[0] = o * o - 2.0f * (R2 + r2) * o + 4 * R2 * q * q + (R2 - r2) * (R2 - r2);
	num_real_roots = SolveQuartic(coeffs, roots);
	bool	intersect = false;
	float	t;
	if (num_real_roots == 0)
		return false;

	t = 1000.0f;
	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > 0.0f)
		{
			intersect = true;
			if (roots[j] < t)
			{
				t = roots[j];
			}
		}
	}
	if (!intersect)
		return false;

	*tr = t;
	return (intersect);
}

/*
** TODO(dmelessa): change later
*/
float	triangle_intersection(t_ray ray, t_triangle triangle, float *tr)
{
	float4	pvec = cross(ray.direction, triangle.vector2);
	float	det = dot(triangle.vector1, pvec);

	if (det < 1e-8 && det > -1e-8)
	{
		return 0.0f;
	}

	float	inv_det = 1.0f / det;
	float4	tvec = ray.origin - triangle.vertex1;
	float	u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1)
	{
		return 0.0f;
	}

	float4	qvec = cross(tvec, triangle.vector1);
	float	v = dot(ray.direction, qvec) * inv_det;
	if (v < 0 || u + v > 1)
	{
		return 0;
	}
	return dot(triangle.vector2,qvec) * inv_det;
}

bool	intersection(t_ray ray, t_obj obj, float *tr)
{
	if (obj.type == sphere)
	{
		return (sphere_intersection(ray, obj, tr));
	}
	else if (obj.type == plane)
	{
		return (plane_intersection(ray, obj, tr));
	}
	else if (obj.type == cylinder)
	{
		return cylinder_intersection(ray, obj, tr);
	}
	else if (obj.type == cone)
	{
		return (cone_intersection(ray, obj, tr));
	}
	else if (obj.type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, tr));
	}
	else if (obj.type == torus)
	{
		return torus_intersecion(ray, obj, tr);
	}
	return (false);
}

void	swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	box_intersection(t_ray ray, t_box box)
{
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
		tx_min = (box.min.x - ox) * a;
		tx_max = (box.max.x - ox) * a;
	}
	else
	{
		tx_min = (box.max.x - ox) * a;
		tx_max = (box.min.x - ox) * a;
	}
	float b = 1.0 / dy;
	if (b >= 0.0f)
	{
		ty_min = (box.min.y - oy) * b;
		ty_max = (box.max.y - oy) * b;
	}
	else
	{
		ty_min = (box.max.y - oy) * b;
		ty_max = (box.min.y - oy) * b;
	}

	float c = 1.0 / dz;
	if (c >= 0.0f)
	{
		tz_min = (box.min.z - oz) * c;
		tz_max = (box.max.z - oz) * c;
	}
	else
	{
		tz_min = (box.max.z - oz) * c;
		tz_max = (box.min.z - oz) * c;
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

	return (t0 < t1 && t1 > 1e-6);
}

int		get_point_color(t_camera camera,
						__constant t_obj *objects, int nobjects,
						int x, int y)
{
	t_ray	ray;
	float	mint = 10001.0f;
	float	t;
	int		i;
	int		id;

	ray = cast_primal_ray(camera, x, y);

	for (i = 0; i < nobjects; i++)
	{
		if (intersection(ray, objects[i], &t))
		{
			if (t < mint && t > 1.0f)
			{
				mint = t;
				id = i;
			}
		}
	}
	if (mint >= 1.0f && mint < 10000.0f)
	{
		// printf("in\n");
		return objects[id].material.color;
	}
	else
		return 0x000000af;
}

__kernel void main(
				__global uint *output_image,
				__constant t_obj *objects, int nobjects,
				t_camera camera,
				__constant t_triangle *triangles)
{
	private int		global_id = get_global_id(0);
	private int		x = global_id % DEFAULT_WIDTH;
	private int		y = global_id / DEFAULT_WIDTH;
	// private t_ray	ray;
	// ray = cast_primal_ray(camera, x, y);
	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
		output_image[global_id] = get_point_color(camera, objects, nobjects, x, y);
	// if (box_intersection(ray, box))
	// 	output[global_id] = 0x0000ffaf;
	// else
	// 	output[global_id] = 0x0000000f;

	// if (triangle_intersection(ray, triangles[0], &t))
		// output[global_id] = 0x0000ffaf;
	// else
		// output[global_id] = 0x0000000f;

	// if (intersection(ray, objects, &t))
		// output[global_id] = (objects + 0)->material.color;
	// else
		// output[global_id] = 0x0000000f;
}
