#ifndef CL_RT_H
# define CL_RT_H

// #include "world.h"

#define K_HUGE_VALUE 1e4f
#define EPSILON 1e-5f
#define SAMPLES 1
#define BOUNCES 2

typedef struct s_scene				t_scene;

typedef struct s_sampler_manager	t_sampler_manager;

typedef struct s_ray				t_ray;
typedef struct s_hit_information	t_hit_info;
typedef struct s_shade_rec			t_shade_rec;

struct s_scene
{
	__constant t_obj		*objects;
	__constant t_triangle	*triangles;
	__constant t_light		*lights;
	int						nobjects;
	int						ntriangles;
	int						nlights;//36 + 80
	t_camera				camera;
	t_light					ambient_light;
	t_ambient_occluder		ambient_occluder;
};

struct					s_sampler_manager
{
	__global t_sampler	*samplers;
	__global float2		*samples;
	__global float2		*disk_samples;
	__global float3		*hemisphere_samples;
};

struct		s_ray
{
	float4	origin;
	float4	direction;
};

struct		s_hit_information
{
	float	t; //ray distance
	float	m;
	float	dv; //dot(ray.direction, object.direction)
	float	xv; //dot(ray.origin - object.origin, object.direction)
};

//TODO(dmelessa): change later
struct			s_shade_rec
{
	t_hit_info	hit_info;	//hit info for calculating hit point and normal
	t_ray		ray;				//for specular highlights
	float4		hit_point;		//world coordinates of hit point
	float4		local_hit_point; //for attaching textures to objects
	float4		normal;			//normal at hit point NOTE: maybe not needed here
							// and we can use local variable
	float4		direction;		//for area lights

	int			id;
	int			depth;			  //recursion depth
	bool		hit_a_triangle; //did the ray hit a triangle
	bool		hit_an_object;	  //or did the ray hit an object?
};

// t_color	float_color_multi(float	c, t_color color);
// t_color	color_sum(t_color a, t_color b);
// t_color	color_multi(t_color a, t_color b);
// t_color	lambertian_f(float kd, t_color color);
// float	glossy_specular_f(float4 camera_direction, float4 normal, float4 light_direction, float ks, float exp);
// t_color	lambertian_rho(float kd, t_color color);

// float4	get_light_direction(t_light light, t_shade_rec shade_rec);
// t_color	get_light_radiance(t_light light);

float4 get_reflected_vector(float4 l, float4 n);
t_color area_light_shade(t_material material,
						 t_shade_rec shade_rec,
						 t_scene scene,
						 t_sampler_manager sampler_manager,
						 t_render_options render_options,
						 uint2 *seed);

// bool	is_intersect(t_ray ray, t_obj obj, t_hit_info *hit_info);
// bool	bbox_intersection(t_ray ray, t_bbox bbox);
// bool	triangle_intersection(t_ray ray, t_triangle triangle, t_hit_info *hit_info);
// float4	get_triangle_normal(t_triangle triangle);
// float4	get_object_normal(float4 point, t_obj object, t_hit_info hit_info);

// void	swap(float *a, float *b);

// float	get_random(unsigned int *seed0, unsigned int *seed1);

// int		SolveQuartic(double c[5], double s[4]);

#endif
