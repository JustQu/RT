#include "world.h"
#include "solver.cl"

struct	s_ray
{
	float4	origin;
	float4	direction;
};
typedef struct s_ray	t_ray;

struct	s_hit_information
{
	float	t;	//ray distance
	float	m;
	float	dv; //dot(ray.direction, object.direction)
	float	xv; //dot(ray.origin - object.origin, object.direction)
	int		id;	//surface id
};
typedef struct s_hit_information t_hit_info;

//TODO(dmelessa): change later
typedef struct	s_shade_rec
{
	bool		hit_an_object;		//did the ray hit an object?
	float4		hit_point;			//world coordinates of hit point
	float4		local_hit_point;	//for attaching textures to objects
	float4		normal;				//normal at hit point
	int			color;
	int			id;
	t_ray		ray;				//for specular highlights
	t_hit_info	hit_info;			//hit info for calculating hit point and normal
	int			depth;				//recursion depth
	float4		direction;			//for area lights
}				t_shade_rec;

/**
** @brief
** cast ray from camera to x,y pos where x,y pixel position of our screen
*/
t_ray	cast_camera_ray(t_camera camera, int x, int y)
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

bool	sphere_intersection(t_ray ray, t_obj sphere, t_hit_info *hit_info)
{
#if 0 // geometric solution

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
	hit_info->t = t;
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
	hit_info->t = b - a;
	if (hit_info->t < 0.0f)
	{
		hit_info->t = b + a;
		if (hit_info->t < 0.0f)
			return false;
	}
	return true;
#endif
}

/**
** there could be mistake
** need some tests
*/
bool	plane_intersection(t_ray ray, t_obj plane, t_hit_info *hit_info)
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
			return (false);
			// *tr = t / denom;
			// return (*tr >= 0);
		}
		else
		{
			hit_info->t = t / denom;
			if (hit_info->t >= 0)
			{
				return (true);
			}
		}
		return false;
	}
	return (false);
}

/*
** TODO(dmelessa): cap cylinder with discs
*/
bool cylinder_intersection(t_ray ray, t_obj cylinder, t_hit_info *hit_info)
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
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < 0.0f)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > 0.0f)
		{
			if (cylinder.maxm > 0.0f)
			{
				float m1 = dv * hit_info->t + xv;
				if (m1 < cylinder.maxm && m1 > 0.0f)
				{
					hit_info->m = m1;
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
			}
			else
			{
				hit_info->dv = dv;
				hit_info->xv = xv;
				return true;
			}
		}
	}
	return false;
}

/*
** TODO(dmelessa): cap cone with disc
*/
bool	cone_intersection(t_ray ray, t_obj cone, t_hit_info *hit_info)
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
		a *= 2.0f;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < 0.0f)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > 0.0f)
		{
			if (cone.maxm != 0.0f || cone.minm != 0)
			{
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm && hit_info->m <= cone.maxm)
				{
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm && hit_info->m <= cone.maxm)
				{
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
			}
			else
			{
				hit_info->dv = dv;
				hit_info->xv = xv;
				return (true);
			}
		}
	}
	return (false);
}

bool	paraboloid_intersection(t_ray ray, t_obj paraboloid, t_hit_info *hit_info)
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
		a *= 2;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < 0.0f)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > 0.0f)
		{
			if (paraboloid.maxm > 0.0f)
			{
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= paraboloid.minm && hit_info->m <= paraboloid.maxm)
					return true;
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= paraboloid.minm && hit_info->m <= paraboloid.maxm)
					return true;
			}
			else
			{
				hit_info->dv = dv;
				hit_info->xv = xv;
				return (true);
			}
		}
	}
	return (false);
}

bool	torus_intersecion(t_ray ray, t_obj torus, t_hit_info *hit_info)
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
	hit_info->m = m;
	hit_info->t = t;
	return (intersect);
}

/*
** TODO(dmelessa): change later
*/
float	triangle_intersection(t_ray ray, t_triangle triangle, t_hit_info *hit_info)
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

float4	get_sphere_normal(float4 point, t_obj *sphere)
{
	return (normalize(point - sphere->origin));
}

float4	get_plane_normal(t_obj *plane)
{
	return (plane->direction);
}

float4	get_cylinder_normal(float4 point, t_obj *cylinder, t_hit_info *hit_info)
{
	float m;
	m = hit_info->dv * hit_info->t + hit_info->xv;
	if (cylinder->maxm > 0.0f) // if cylinder is not infinite
		return (normalize(point - cylinder->origin - cylinder->direction * m));
	return (normalize(point - cylinder->origin - cylinder->direction * m));
}

float4	get_cone_normal(float4 point, t_obj *cone, t_hit_info *hit_info)
{
	float m = hit_info->dv * hit_info->t + hit_info->xv;
	return (normalize(point - cone->origin - cone->r2 * cone->direction * m));
}

float4	get_paraboloid_normal(float4 point, t_obj *paraboloid, t_hit_info *hit_info)
{
	if (paraboloid->maxm > 0.0f)
		return (normalize(point - paraboloid->origin - paraboloid->direction *
			(hit_info->m + paraboloid->r)));
	float m = hit_info->dv * hit_info->t + hit_info->xv;
	return (normalize(point - paraboloid->origin - paraboloid->direction * (m +
		paraboloid->r)));
}

float4	get_triangle_normal(t_triangle *triangle)
{
}

float4	get_torus_normal(float4 point, t_obj *torus, t_hit_info *hit_info)
{
	float	k;
	float	m;
	float4	A;

	//point = 1.001f * point;
	k = dot(point - torus->origin, torus->direction);
	A = point - k * torus->direction;
	m = sqrt(torus->r2 * torus->r2 - k * k);
	return normalize(point - A - (torus->origin - A) * (m / (torus->r + m)));
}

float4	get_object_normal(float4 point, t_obj *object, t_hit_info *hit_info)
{
	if (object->type == sphere)
	{
		return get_sphere_normal(point, object);
	}
	else if (object->type == plane)
	{
		return (get_plane_normal(object));
	}
	else if (object->type == cylinder)
	{
		return (get_cylinder_normal(point, object, hit_info));
	}
	else if (object->type == cone)
	{
		return (get_cone_normal(point, object, hit_info));
	}
	else if (object->type == paraboloid)
	{
		return (get_paraboloid_normal(point, object, hit_info));
	}
	else if (object->type == torus)
	{
		return (get_torus_normal(point, object, hit_info));
	}
}

bool	is_intersect(t_ray ray, t_obj obj, t_hit_info *hit_info)
{
	if (obj.type == sphere)
	{
		return (sphere_intersection(ray, obj, hit_info));
	}
	else if (obj.type == plane)
	{
		return (plane_intersection(ray, obj, hit_info));
	}
	else if (obj.type == cylinder)
	{
		return cylinder_intersection(ray, obj, hit_info);
	}
	else if (obj.type == cone)
	{
		return (cone_intersection(ray, obj, hit_info));
	}
	else if (obj.type == paraboloid)
	{
		return (paraboloid_intersection(ray, obj, hit_info));
	}
	else if (obj.type == torus)
	{
		return torus_intersecion(ray, obj, hit_info);
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

bool	bbox_intersection(t_ray ray, t_box box)
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

t_color	color_sum(t_color a, t_color b)
{
	t_color res;
	res.b = clamp(a.b + b.b, 0, 255);
	res.g = clamp(a.g + b.g, 0, 255);
	res.r = clamp(a.r + b.r, 0, 255);
	return (res);
}

t_color	color_multi(t_color a, t_color b)
{
	t_color	res;

	res.r = (uchar)clamp(a.r * b.r, 0, 255);
	res.g = (uchar)clamp(a.g * b.g, 0, 255);
	res.b = (uchar)clamp(a.b * b.b, 0, 255);
	return (res);
}

t_color	float_color_multi(float	c, t_color color)
{
	t_color	res;

	res.b = clamp(c * color.b, 0.0f, 255.0f);
	res.g = clamp(c * color.g, 0.0f, 255.0f);
	res.r = clamp(c * color.r, 0.0f, 255.0f);
	return (res);
}

t_color	lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * (float)M_1_PI, color));
	// t_color	res;

	// res.r = clamp(kd * color.r * (float) M_1_PI, 0.0f, 255.0f);
	// res.g = clamp(kd * color.g * (float) M_1_PI, 0.0f, 255.0f);
	// res.b = clamp(kd * color.b * (float) M_1_PI, 0.0f, 255.0f);
	// return (res);
}

t_color	lambertian_rho(float kd, t_color color)
{
	t_color	res;

	res = float_color_multi(kd, color);
	return (res);
}

float4	get_light_direction(t_light light, t_shade_rec *shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec->hit_point));
}

t_color	get_light_radiance(t_light light)
{
	t_color	color;

	if (light.type == ambient)
	{
		color.r = clamp(light.color.r * light.ls, 0.0f, 255.0f);
		color.g = clamp(light.color.g * light.ls, 0.0f, 255.0f);
		color.b = clamp(light.color.b * light.ls, 0.0f, 255.0f);
		return (color);
	}
}

//matte coloring
int		shade_object(t_obj object, t_shade_rec *shade_rec, __constant t_light *lights, int nlights, t_light ambient_light)
{
	float4	normal;
	float4	light_direction;
	float	dirdotn;
	t_color	color;
	t_color	color_tmp;

	shade_rec->ray.direction = -shade_rec->ray.direction;
	color_tmp = float_color_multi(ambient_light.ls, lambertian_rho(object.material.ka, object.material.color));
	color_tmp.value = 0;
	light_direction = get_light_direction(lights[0], shade_rec);
	normal = get_object_normal(shade_rec->hit_point, &object, &shade_rec->hit_info);
	// if (dot(normal, shade_rec->ray.direction) < 0) normal = -normal;
	dirdotn = dot(normal, light_direction);
	if (dirdotn >= 0.0f)
	{
		color = lambertian_f(object.material.kd, object.material.color);
		color = float_color_multi(lights[0].ls * dirdotn, color);
		color = color_sum(color_tmp, color);
	}
	else
		color = color_tmp;
	return (color.value);
}

bool	hit_objects(t_ray ray, t_shade_rec *shade_rec, __constant t_obj *objects, int nobjects)
{
	float		t;
	float		tmin = 10001.0f; //huge value

	shade_rec->hit_an_object = false;
	for (int i = 0; i < nobjects; i++)
	{
		shade_rec->hit_info.t = tmin;
		if (is_intersect(ray, objects[i], &shade_rec->hit_info) &&
			shade_rec->hit_info.t < tmin)
		{
			shade_rec->hit_an_object = true;
			tmin = shade_rec->hit_info.t;
			shade_rec->id = i;
		}
	}
	shade_rec->hit_info.t = tmin;
	return (shade_rec->hit_an_object);
}

/**
**@brief
** получить цвет пикселя в позиции x,y экрана, используя камеру camera
*/
int		trace_ray(t_camera camera,
					__constant t_obj *objects, int nobjects,
					__constant t_light *lights, int nlights,
					t_light ambient_light,
					int x, int y)
{
#if 1
	t_ray		ray;
	t_shade_rec	shade_rec;

	ray = cast_camera_ray(camera, x, y);
	if (hit_objects(ray, &shade_rec, objects, nobjects))
	{
		shade_rec.ray = ray;	//for specular reflection
		// shade_rec.hit_info.t += 0.0005;
		shade_rec.hit_point = shade_rec.hit_info.t * shade_rec.ray.direction + shade_rec.ray.origin;
		return (shade_object(objects[shade_rec.id],
							&shade_rec,
							lights, nlights,
							ambient_light));
	//	return (objects[shade_rec.hit_info.id].material.color);
	}
	else
		return 0x000000af;
#else
	t_ray		ray;
	t_hit_info	hit_info;
	t_shade_rec	shade_rec;
	float		mint = 10001.0f; //attention!
	int			i;
	for (i = 0; i < nobjects; i++)
	{
		if (is_intersect(ray, objects[i], &hit_info) &&
			hit_info.t < mint && hit_info.t > 1.0f)
		{
			mint = hit_info.t;
			hit_info.id = i;
		}
	}
	if (mint >= 1.0f && mint < 10000.0f)//atention!
	{
		//cast secondary rays
		return objects[hit_info.id].material.color;
	}
	else
		return 0x000000af;
#endif
}

__kernel void main(
				__global uint *output_image,
				__constant t_obj *objects,
				int nobjects,
				__constant t_light *lights,
				int nlights,
				t_camera camera,
				t_light ambient_light,
				__constant t_triangle *triangles)
{
	private int		global_id = get_global_id(0);
	private int		x = global_id % DEFAULT_WIDTH;
	private int		y = global_id / DEFAULT_WIDTH;

	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
		output_image[global_id] = trace_ray(camera, objects, nobjects,
			lights, nlights, ambient_light, x, y);
}
