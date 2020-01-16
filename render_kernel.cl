#include "defines.h"

typedef enum	e_objs
{
	none,
	sphere,
	plane,
	cone,
	cylinder,
	light,
	camera
}				t_obj_type;

typedef struct	s_ray
{
	float3	origin;
	float3	dir;
}				t_ray;

typedef struct	s_sphere
{
	float radius;
	float3 pos;
	float3 emi;
	float3 color;
}				t_sphere;

typedef struct	s_material
{
	int		color;
	float	kd;
	float	ks;
	float	n;
}				t_material;

typedef struct	s_plane
{
	float4		nv;
}				t_plane;

typedef struct	s_cone
{
	float3		dir;
	float		angle;
	float		k;
	float		k2;
}				t_cone;

typedef struct	s_cylinder
{
	float4		dir;
	float		radius;
}				t_cylinder;

typedef struct	s_obj
{
	t_obj_type	type;
	float4		c_s;
	float4		origin;
	float4		hit_point;
	float4		surf_normal;
	t_material	mat;
	float		t;
	void		*data;
}				t_obj;


t_ray	createCamRay(const float x, const float y)
{
	t_ray	ray;

	float	fx = (float)x / (float)SCREEN_WIDTH;
	float	fy = (float)y / (float)SCREEN_HEIGHT;
	float	ratio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float	fx2 = (fx - 0.5) * ratio;
	float	fy2 = fy - 0.5;
	float3	pix_pos = (float3)(fx2, -fy2, 0);

	ray.origin = (float3)(0, 0, 40);
	ray.dir = normalize(pix_pos - ray.origin);

	return ray;
}

bool	sphere_intersection(t_sphere *sp, t_ray *ray, float *t)
{
	float3 rayToCenter = sp->pos - ray->origin;

	float b = dot(rayToCenter, ray->dir);
	float c = dot(rayToCenter, rayToCenter) - sp->radius * sp->radius;
	float disc = b * b - c; 

	if (disc < 0.0f)
		return false;
	else
		*t = b - sqrt(disc);
	if (*t < 0.0f)
	{
		*t = b + sqrt(disc);
		if (*t < 0.0f)
			return false; 
	}
	else return true;
}

float	noise(float x, float y, float z)
{
	float num = 0.0f;
	return fract(sin(x*112.9898f + y*179.233f + z*237.212f) * 43758.5453f, &num);
}

__kernel void render(__global int *C) {
	int i = get_global_id(0);
	int x = i % SCREEN_WIDTH;
	int y = i / SCREEN_WIDTH;
	t_ray ray;
	t_sphere sp;
	sp.radius = 0.3f;
	sp.pos = (float3)(0.0f, 0.0f, 5.0f);
	sp.color = (float3)(200, 99, 88);
	float t = 1e20;
	float3 color = float3(0.0f, 0.0f, 0.0f);
	ray = createCamRay(x, y);
	sphere_intersection(&sp, &ray, &t);
	if (t <= 1e19)
		color = sp.color;
	else
	{
		int fx = (float)(x) / (float)SCREEN_WIDTH * 255;
		int fy = (float)(y) / (float)SCREEN_HEIGHT * 255;
		color += (float3)((int)(fx) , (int)(fy) , (int)(200));
	}
	C[i] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
}
