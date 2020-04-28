#include "rt.h"

cl_float4 norm4(cl_float4 vec)
{
	float	magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x = vec.x / magnitude;
	vec.y = vec.y / magnitude;
	vec.z = vec.z / magnitude;
	return (vec);
}

cl_float4	cross_product(cl_float4 a, cl_float4 b)
{
	cl_float4 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = -a.x * b.z + a.z * b.x;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

//todo: check
void	compute_uvw(t_camera *camera)
{
	camera->w.x = -camera->direction.x;
	camera->w.y = -camera->direction.y;
	camera->w.z = -camera->direction.z;
	camera->w.w = 0.0f;
	camera->w = norm4(camera->w);
	camera->u = cross_product(camera->up, camera->w);
	camera->u.x = -camera->u.x; //doing this because we are using left handed coordinate system
	camera->u.y = -camera->u.y;
	camera->u.z = -camera->u.z;
	camera->v = cross_product(camera->w, camera->u);
	camera->v.x = -camera->v.x;
	camera->v.y = -camera->v.y;
	camera->v.z = -camera->v.z;
}

/**
** @todo
** @brief
**
** @param camera
** @param axis 0 - x, 1 - y, 2 - z
** @param angle_degrees
** @return ** void
*/
void	rotate_camera(t_camera *camera, int axis, float angle_degrees)
{
	//rotate u, v, w
}
