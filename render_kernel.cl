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
	float4	origin;
	float4	dir;
}				t_ray;

typedef struct	s_material
{
	int3	color;
	float	kd;
	float	ks;
	float	n;
}				t_material;

typedef struct	s_obj
{
	t_obj_type	type;
	float4		c_s;
	float4		origin;
	float4		hit_point;
	float4		surf_normal;
	t_material	mat;
	float		t;
	float4		dir;
	float		r;
	float		r2;
	float		angle;
	
}				t_obj;

typedef	struct	s_light_source
{
	float4		origin;
	float		intensity;
	float4		c_s;
}				t_light_source;

typedef struct		s_world
{
	t_obj			*objs;
	int				nobjs;
	t_light_source	*lights;
	int				nlights;
}					t_world;

t_ray	createCamRay(const float x, const float y)
{
	t_ray	ray;

	float	fx = (float)x / (float)SCREEN_WIDTH;
	float	fy = (float)y / (float)SCREEN_HEIGHT;
	float	ratio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float	fx2 = (fx - 0.5) * ratio;
	float	fy2 = fy - 0.5;
	float4	pix_pos = (float4)(fx2, -fy2, 0, 0);

	ray.origin = (float4)(0, 0, 40, 0);
	ray.dir = normalize(pix_pos - ray.origin);

	return ray;
}

bool	sphere_intersection(t_ray *ray, t_obj *sp)
{
	float4 rayToCenter = sp->origin - ray->origin;

	float b = dot(rayToCenter, ray->dir);
	float c = dot(rayToCenter, rayToCenter) - sp->r2;
	float disc = b * b - c; 

	if (disc < 0.0f)
		return false;
	else
		sp->t = b - sqrt(disc);
	if (sp->t < 0.0f)
	{
		sp->t = b + sqrt(disc);
		if (sp->t < 0.0f)
			return false; 
	}
	else return true;
}

float	noise(float x, float y, float z)
{
	float num = 0.0f;
	return fract(sin(x*112.9898f + y*179.233f + z*237.212f) * 43758.5453f, &num);
}

__kernel void render(__global int *C, __global t_obj *jojo, const int nobjs) {
	int i = get_global_id(0);
	int x = i % SCREEN_WIDTH;
	int y = i / SCREEN_WIDTH;
	t_ray ray;
	t_obj sp = jojo[0];
	sp.t = 1e20;
	int3 color = int3(0.0f, 0.0f, 0.0f);
	ray = createCamRay(x, y);
	sphere_intersection(&ray, &sp);
	if (sp.t <= 1e19)
		color = sp.mat.color;
	else
	{
		int fx = (float)(x) / (float)SCREEN_WIDTH * 255;
		int fy = (float)(y) / (float)SCREEN_HEIGHT * 255;
		color = (int3)(fx, fy, 200);
	}
	C[i] = (int)color.x << 16 | (int)color.y << 8 | (int)color.z;
	// if (i == 0)
		// printf("%f, %d\n", jojo[0].r, nobjs);
	// C[i] = jojo[0].r;
}
