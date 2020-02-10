struct	s_ray
{
	float4	origin;
	float4	direction;
};
typedef struct s_ray	t_ray;

struct s_sphere
{
	float4	origin;
	float	radius;
	int		color;
};
typedef struct s_sphere	t_sphere;

t_ray	cast_ray(int x, int y)
{
	t_ray	ray;

	ray.origin = (float4)((float)x, (float)y, 0.0f, 0.0f);
	ray.direction = (float4)(0.0f, 0.0f, 1.0f, 0.0f);
	return ray;
}

bool	sphere_intersection(t_ray ray, t_sphere sphere, float *tr)
{
#if 0 // geometric solution

	float4 L = sphere.origin - ray.origin;
	float tca = dot(L, ray.direction);
	if (tca < 0.0f)
		return false;
	float d2 = dot(L, L) - tca * tca;
	if (d2 > sphere.radius * sphere.radius) //r^2 should be precomputed
		return false;
	float thc = sqrt(sphere.radius * sphere.radius);
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
	float c = dot(L, L) - sphere.radius * sphere.radius;
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

__kernel void render2(
				__global uint *output)
{
	private int			global_id = get_global_id(0);
	private int			local_id = get_local_id(0);
	private int			x = global_id % 800;
	private int			y = global_id / 800;
	// t_sphere	sphere1;

	private t_ray		ray;
	ray = cast_ray(x, y);

	private int	i;
	private float t = 0;
	private int id;
	private float maxt = 0;

	// for (i = 0; i < 10; i++)
	// {
	// 	if (global_id == 128000)
	// 		printf("%d:( %f %f %f %f) %f %d\n",i, spheres[i].origin.x,spheres[i].origin.y, spheres[i].origin.z, spheres[i].origin.w, spheres[i].radius, spheres[i].color);
	// 	if (sphere_intersection(ray, spheres[i], &t) == true)
	// 	{
	// 		if (t > maxt)
	// 			id = i;
	// 		// output[global_id] = spheres[i].color;
	// 	}

	// 		// output[global_id] = 0x000000af;
	// }
	// if (t > 0.0f)
	// 	output[global_id] = spheres[id].color;
	// else
		 output[global_id] = 0x000f0000;
}
