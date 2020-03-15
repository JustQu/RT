#include "world.h"
#include "solver.cl"
#include "cl_rt.h"

#define EPSILON 1e-5
#define K_HUGE_VALUE 1e4f

static float get_random(unsigned int *seed0, unsigned int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

// int rand(int* seed) // 1 <= *seed < m
// {
//     int const a = 16807; //ie 7**5
//     int const m = 2147483647; //ie 2**31-1

//     *seed = ((long)(*seed * a)) % m;
//     return (*seed);
// }

// float	get_float_rand()
// {
// 	return ((float)rand(&seed) / (float)2147483647);
// }

/******************************** OBJECT INTERSECTION **************************************/

 bool	bbox_intersection(t_ray ray, t_bbox bbox)
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
		tx_min = (bbox.min.x - ox) * a;
		tx_max = (bbox.max.x - ox) * a;
	}
	else
	{
		tx_min = (bbox.max.x - ox) * a;
		tx_max = (bbox.min.x - ox) * a;
	}
	float b = 1.0 / dy;
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

	float c = 1.0 / dz;
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

	return (t0 < t1 && t1 > 1e-6);
}

 bool	sphere_intersection(t_ray ray, t_obj sphere, t_hit_info *hit_info)
{
#if 1 // geometric solution

	float4	L = sphere.origin - ray.origin;
	float	tca = dot(L, ray.direction);
	if (tca < 0.0f)
		return false;

	float	d2 = dot(L, L) - tca * tca;
	if (d2 > sphere.r2) //r^2 should be precomputed
		return false;

	float	thc = sqrt(sphere.r2 - d2);
	float	t = tca - thc;
	if (t < 0.0f)
	{
		t = tca + thc;
		if (t < 0.0f)
			return false;
	}
	hit_info->t = t;
	return (true);

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

	denom = dot(ray.direction, plane.direction);
	if (denom != 0)
	{
		a = plane.origin - ray.origin;
		t = dot(a, plane.direction);
		if (t * denom < 0.0f) //different signes
		{
			return (false);
			// *tr = t / denom;
			// return (*tr >= 0);
		}
		else
		{
			hit_info->t = t / denom;
			if (hit_info->t >= EPSILON)
			{
				hit_info->dv = denom;
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
	if (disc >= EPSILON)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < EPSILON)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
		{
			if (cylinder.maxm > 0.0f)
			{
				float m1 = dv * hit_info->t + xv;
				if (m1 < cylinder.maxm && m1 > EPSILON)
				{
					hit_info->m = m1;
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cylinder.minm + EPSILON && hit_info->m <= cylinder.maxm)
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
	if (disc >= EPSILON)
	{
		a *= 2.0f;
		disc = sqrt(disc);
		float t1 = (-b - disc) / a;
		float t2 = (-b - disc) / a;
		if (t1 < 0)
			hit_info->t = t2;
		else if (t2 > 0 && t2 < t1)
			hit_info->t = t2;
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < EPSILON)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
		{
			if (cone.maxm != 0.0f || cone.minm != 0)
			{
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm + EPSILON && hit_info->m <= cone.maxm)
				{
					hit_info->dv = dv;
					hit_info->xv = xv;
					return true;
				}
				hit_info->t = (-b + disc) / a;
				hit_info->m = dv * hit_info->t + xv;
				if (hit_info->m >= cone.minm + EPSILON && hit_info->m <= cone.maxm)
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
	if (disc >= EPSILON)
	{
		a *= 2;
		disc = sqrt(disc);
		hit_info->t = (-b - disc) / a;
		if (hit_info->t < 0.0f)
			hit_info->t = (-b + disc) / a;
		if (hit_info->t > EPSILON)
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
	if (!bbox_intersection(ray, torus.bounding_box))
		return false;
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
		if (roots[j] > EPSILON)
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
		return 0.0f;

	float	inv_det = 1.0f / det;
	float4	tvec = ray.origin - triangle.vertex1;
	float	u = dot(tvec, pvec) * inv_det;
	if (u < EPSILON || u > 1)
		return 0.0f;

	float4	qvec = cross(tvec, triangle.vector1);
	float	v = dot(ray.direction, qvec) * inv_det;
	if (v < EPSILON || u + v > 1)
		return 0;
	hit_info->t = dot(triangle.vector2, qvec) * inv_det;
	return hit_info->t > EPSILON;
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

/*******************************************************************************************/

/************** NORMAL TO OBJECT ******************************/
 float4	get_sphere_normal(float4 point, t_obj sphere)
{
	return (normalize(point - sphere.origin));
}

 float4	get_plane_normal(t_obj plane, t_hit_info hit_info)
{
	if (hit_info.dv < 0.0F)
		return plane.direction;
	else
		return -(plane.direction);
}

 float4	get_cylinder_normal(float4 point, t_obj cylinder, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cylinder.origin - cylinder.direction * m));
}

 float4	get_cone_normal(float4 point, t_obj cone, t_hit_info hit_info)
{
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - cone.origin - cone.r2 * cone.direction * m));
}

 float4	get_paraboloid_normal(float4 point, t_obj paraboloid, t_hit_info hit_info)
{
	if (paraboloid.maxm > 0.0f)
		return (normalize(point - paraboloid.origin - paraboloid.direction *
			(hit_info.m + paraboloid.r)));
	float m = hit_info.dv * hit_info.t + hit_info.xv;
	return (normalize(point - paraboloid.origin - paraboloid.direction * (m +
		paraboloid.r)));
}

inline float4	get_triangle_normal(t_triangle triangle)
{
	return (triangle.normal);
}

 float4	get_torus_normal(float4 point, t_obj torus, t_hit_info hit_info)
{
	float	k;
	float	m;
	float4	A;

	point = 1.0001f * point;
	k = dot(point - torus.origin, torus.direction);
	A = point - k * torus.direction;
	m = sqrt(torus.r2 * torus.r2 - k * k);
	return normalize(point - A - (torus.origin - A) * (m / (torus.r + m)));
}

 float4	get_object_normal(float4 point, t_obj object, t_hit_info hit_info)
{
	if (object.type == sphere)
	{
		return get_sphere_normal(point, object);
	}
	else if (object.type == plane)
	{
		return (get_plane_normal(object, hit_info));
	}
	else if (object.type == cylinder)
	{
		return (get_cylinder_normal(point, object, hit_info));
	}
	else if (object.type == cone)
	{
		return (get_cone_normal(point, object, hit_info));
	}
	else if (object.type == paraboloid)
	{
		return (get_paraboloid_normal(point, object, hit_info));
	}
	else if (object.type == torus)
	{
		return (get_torus_normal(point, object, hit_info));
	}
}
/*******************************************************************************/

/**
** @brief
** cast ray from camera to x,y pos where x,y pixel position of our screen
*/
 t_ray	cast_camera_ray(t_camera camera, float x, float y)
{

	t_ray	ray;
	float	px;
	float	py;
#if 0 //pinhole camera

	px = (2.0f * ((x + 0.5f) / DEFAULT_WIDTH) - 1.0f) * camera.angle * camera.ratio;
	py = (1.0f - 2.0f * (y + 0.5f) / DEFAULT_HEIGHT) * camera.angle;
	ray.origin = camera.origin;
	ray.direction = (float4)(px, py, 1.0f, 0.0f);//need to rotate vector if we have rotated camera
	ray.direction = normalize(ray.direction);
#elif 0
	px = 1.0f * (x - 0.5 * (DEFAULT_WIDTH - 1));
	py = 1.0f * (y - 0.5 * (DEFAULT_HEIGHT - 1));
	ray.origin.z = 100;
	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.direction = (float4)(px, py, 1.0f, 0.0f);//need to rotate vector if we have rotated camera
	ray.direction = normalize(ray.direction);
#else
	px = 1.0f /*pixel_size*/ *(x - 0.5f * (DEFAULT_WIDTH));
	py = 1.0f * (-y + 0.5f * (DEFAULT_HEIGHT));
	ray.origin = (float4)(px, py, 100.0f, 0.0f);
	ray.direction = (float4)(0.0f, 0.0f, -1.0f, 0.0f);
#endif
	return ray;
}

 void	swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

 t_color	color_sum(t_color a, t_color b)
{
	t_color res;
	res.b = clamp(a.b + b.b, 0, 255);
	res.g = clamp(a.g + b.g, 0, 255);
	res.r = clamp(a.r + b.r, 0, 255);
	return (res);
}

//NOTE: probably not needed
// component-wise colors multiplication
inline t_color	color_multi(t_color a, t_color b)
{
	t_color	res;

	res.r = (uchar)clamp(a.r * b.r, 0, 255);
	res.g = (uchar)clamp(a.g * b.g, 0, 255);
	res.b = (uchar)clamp(a.b * b.b, 0, 255);
	return (res);
}

inline t_color	float_color_multi(float	c, t_color color)
{
	t_color	res;

	res.b = clamp(c * color.b, 0.0f, 255.0f);
	res.g = clamp(c * color.g, 0.0f, 255.0f);
	res.r = clamp(c * color.r, 0.0f, 255.0f);
	return (res);
}

inline float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = -l + 2 * dot(l, n) * n;
	return normalize(r);
}

// float
 t_color
lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * (float)M_1_PI, color));
	// return (kd * M_1_PI);
}

 float	glossy_specular_f(float4 camera_direction, float4 normal, float4 light_direction, float ks, float exp)
{
	float		res = 0;
	float4	r = get_reflected_vector(light_direction, normal);
	float	rdotdir = dot(r, camera_direction);

	if (rdotdir > 0)
		res = ks * pow(rdotdir, exp);
	return res;
}

 t_color	lambertian_rho(float kd, t_color color)
{
	t_color	res;

	res = float_color_multi(kd, color);
	return (res);
}

 float4	get_light_direction(t_light light, t_shade_rec shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec.hit_point));
	else if (light.type == directional)
		return -normalize(light.direction);
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

 bool	shadow_hit_object(t_ray shadow_ray, t_obj obj, t_hit_info *hit_info)
{
	if (!obj.shadows)
		return false;
	return (is_intersect(shadow_ray, obj, hit_info));
}

//TODO: triangles
 bool	shadow_hit(t_light light, t_ray shadow_ray, t_shade_rec shade_rec, __constant t_obj *objects, int nobjects, __constant t_triangle *triangles, int ntriangles)
{
	float	t;
	float	d = distance(light.origin, shadow_ray.origin);

	for (int i = 0; i < nobjects; i++)
	{
		if (shadow_hit_object(shadow_ray, objects[i], &shade_rec.hit_info) &&
			shade_rec.hit_info.t < d)
			return (true);
	}
	return (false);
}

/*
lights can optionally cast shadows
objects can optionally cast shadows
materials can optionally cast shadows
*/
//TODO(dmelessa): light colors
//note we don't need an object. We should pass only material nad compute normal
//in function before
 t_color		shade_object(t_material material, t_shade_rec shade_rec,
	__constant t_light *lights, int nlights, t_light ambient_light,
	__constant t_obj *objects, int nobjects,
	__constant t_triangle *triangles, int ntriangles,
	t_render_options options)
{
	float4	normal;
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	//revert camera ray for specular light
	// return material.color;
	shade_rec.ray.direction = -shade_rec.ray.direction;

	//compute ambient light using ka coefficent of the materail
	color = float_color_multi(ambient_light.ls,
					lambertian_rho(material.ka, material.color));

	//compute sahding for each light source
	for (int i = 0; i < nlights; i++)
	{
		bool	in_shadow = false;

		//compute light direction at hit point
		light_direction = get_light_direction(lights[i], shade_rec);

		//multiplying by 0.999f to avoid self shadowing error
		t_ray	shadow_ray = {.origin = shade_rec.hit_point * 0.999f, .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(lights[i], shadow_ray, shade_rec, objects, nobjects, triangles, ntriangles);

		if (!in_shadow)
		{
			//compute angle between normal at the hit point and light direction
			dirdotn = dot(shade_rec.normal, light_direction);

			//if angle > 0 then hit point is receivingl light
			if (dirdotn > 0.0f)
			{
				//compute glossy_specular coefficient
				float a = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, material.ks, material.exp) ;

				//compute lambertian color
				color_tmp = lambertian_f(material.kd, material.color);

				//sum lambertian color and glossy specular color
				color_tmp = color_sum(color_tmp, float_color_multi(a, (t_color){.value=0x00ffffff}));

				//compute how much light the point receives depends on angle between the normal at this point and 	light direction
				color_tmp = float_color_multi(lights[i].ls * (dirdotn), color_tmp);
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

//TODO(dmelessa): shading both sides of surface §14
 bool	hit_nearest_object(t_ray ray, t_shade_rec *shade_rec,
					 __constant t_obj *objects, int nobjects,
					 __constant t_triangle *triangles, int ntriangles)
{
	float		t;
	t_hit_info	last_rec;

	last_rec.t = K_HUGE_VALUE;
	shade_rec->hit_an_object = false;
	shade_rec->hit_an_triangle = false;
	for (int i = 0; i < nobjects; i++)
	{
		if (is_intersect(ray, objects[i], &shade_rec->hit_info) &&
			shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_an_object = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	for (int i = 0; i < ntriangles; i++)
	{
		if (triangle_intersection(ray, triangles[i], &shade_rec->hit_info) &&
			shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_an_triangle = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	shade_rec->hit_info = last_rec;
	return (shade_rec->hit_an_object || shade_rec->hit_an_triangle);
}

t_color	get_ray_color(t_ray ray, __constant t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__constant t_light *lights, int nlights,
					t_light ambient_light,
					t_render_options options)
{
	t_shade_rec	shade_rec;
	t_color		color;

	color.value = 0x000000af;
	if (hit_nearest_object(ray, &shade_rec, objects, nobjects,
			triangles, ntriangles))
		{
			shade_rec.ray = ray;	//for specular reflection
			shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction
				+ shade_rec.ray.origin;
			if (shade_rec.hit_an_triangle)
			{
				shade_rec.normal = get_triangle_normal(triangles[shade_rec.id]);
				color = shade_object(triangles[shade_rec.id].material, shade_rec,
									lights, nlights, ambient_light,
									objects, nobjects, triangles, ntriangles, options);
			}
			else
			{
				shade_rec.normal = get_object_normal(shade_rec.hit_point,
					objects[shade_rec.id], shade_rec.hit_info);
				color = shade_object(objects[shade_rec.id].material,
									shade_rec, lights, nlights,	ambient_light,
									objects, nobjects, triangles, ntriangles, options);
			}
		}
	return (color);
}

float2	sample_unit_square(__global float2 *sampler_set, t_render_options options, int *count)
{
	float2	sp;
	sp = sampler_set[*count % (options.sampler_info.num_samples * options.sampler_info.num_sets)];
	*count = *count + 1;
	return sp;
}

/**
**@brief
** получить цвет пикселя в позиции x,y экрана, используя камеру camera
*/
 int		get_pixel_color(t_camera camera,
					__constant t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__constant t_light *lights, int nlights,
					t_light ambient_light,
					int x, int y,
					t_render_options options,
					__global float2 *sampler_set)
{
#if 1
	t_ray		ray;
	t_color		color;
	t_color		acc;
	float4		test = 0;
	int			n = (int)sqrt((float)options.sampler_info.num_samples);

	color.value = 0;
	acc.value = 0;
	if (options.sampler_info.type == jitter)
	{
		float jitterMatrix[4 * 2] = {
			-1.0/4.0,  3.0/4.0,
	 		3.0/4.0,  1.0/3.0,
			-3.0/4.0, -1.0/4.0,
	 		1.0/4.0, -3.0/4.0,
		};
		for (int sample = 0; sample < 4; ++sample)
		{
			float dx = (x + jitterMatrix[2 * sample]);
			float dy = (y + jitterMatrix[2 * sample + 1]);
			ray = cast_camera_ray(camera, dx, dy);
			acc = get_ray_color(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
			test.x += acc.r;
			test.y += acc.g;
			test.z += acc.b;
		}
		color.r = test.x / options.sampler_info.num_samples;
		color.g = test.y / options.sampler_info.num_samples;
		color.b = test.z / options.sampler_info.num_samples;
	}
	else if (options.sampler_info.type == regular_grid)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
		{
			float	dx = (x + (j + 0.5f) / n);
			float	dy = (y + (i + 0.5f) / n);
			ray = cast_camera_ray(camera, dx, dy);
			acc = get_ray_color(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
			test.x += acc.r;
			test.y += acc.g;
			test.z += acc.b;
		}
		color.r = test.x / options.sampler_info.num_samples;
		color.g = test.y / options.sampler_info.num_samples;
		color.b = test.z / options.sampler_info.num_samples;
	}
	else if (options.sampler_info.type == rand_jitter)
	{
		int	count = get_global_id(0) / 25;
		for (int j = 0; j < options.sampler_info.num_samples; j++)
		{
			float2	sp = sample_unit_square(sampler_set, options, &count);
			float dx = x + sp.x;
			float dy = y + sp.y;
			ray = cast_camera_ray(camera, dx, dy);
			acc = get_ray_color(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
			test.x += acc.r;
			test.y += acc.g;
			test.z += acc.b;
		}
		color.r = test.x / options.sampler_info.num_samples;
		color.g = test.y / options.sampler_info.num_samples;
		color.b = test.z / options.sampler_info.num_samples;
		// int xx = x;
		// int yy = y;
		// for (int i = 0; i < n; i++)
		// 	for (int j = 0; j < n; j++)
		// {
		// 	float	dx = (x + get_random(&xx, &yy));
		// 	float	dy = (y + get_random(&yy, &xx));
		// 	ray = cast_camera_ray(camera, dx, dy);
		// 	acc = get_ray_color(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
		// 	test.x += acc.r;
		// 	test.y += acc.g;
		// 	test.z += acc.b;
		// }
		// color.r = test.x / options.sampler_info.num_samples;
		// color.g = test.y / options.sampler_info.num_samples;
		// color.b = test.z / options.sampler_info.num_samples;
	}
	else if (options.sampler_info.type == none)
	{
		ray = cast_camera_ray(camera, x, y);
		color = get_ray_color(ray, objects, nobjects, triangles, ntriangles, lights, nlights, ambient_light, options);
	}
	return (color.value);
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
				__constant t_obj *objects, int nobjects,
				__constant t_light *lights, int nlights,
				t_camera camera,
				t_light ambient_light,
				__constant t_triangle *triangles, int ntriangles,
				t_render_options options,
				__global float2 *samples)
{
	private int		global_id = get_global_id(0);
	private int		x = global_id % DEFAULT_WIDTH;
	private int		y = global_id / DEFAULT_WIDTH;

	if (global_id < DEFAULT_WIDTH * DEFAULT_HEIGHT)
	{
		output_image[global_id] = get_pixel_color(camera, objects, nobjects,
			triangles, ntriangles, lights, nlights, ambient_light, x, y, options, samples);
	}
}
