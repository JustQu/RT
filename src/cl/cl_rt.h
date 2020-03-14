#ifndef CL_RT_H
# define CL_RT_H

struct s_ray
{
	float4 origin;
	float4 direction;
};
typedef struct s_ray t_ray;

struct s_hit_information
{
	float t; //ray distance
	float m;
	float dv; //dot(ray.direction, object.direction)
	float xv; //dot(ray.origin - object.origin, object.direction)
};
typedef struct s_hit_information t_hit_info;

//TODO(dmelessa): change later
typedef struct s_shade_rec
{
	t_hit_info hit_info;	//hit info for calculating hit point and normal
	t_ray ray;				//for specular highlights
	float4 hit_point;		//world coordinates of hit point
	float4 local_hit_point; //for attaching textures to objects
	float4 normal;			//normal at hit point NOTE: maybe not needed here
							// and we can use local variable
	float4 direction;		//for area lights

	int id;
	int depth;			  //recursion depth
	bool hit_an_triangle; //did the ray hit a triangle
	bool hit_an_object;	  //or did the ray hit an object?
} t_shade_rec;

#endif
