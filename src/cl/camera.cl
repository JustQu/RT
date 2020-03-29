
// #include "cl_rt.h"

/**
** @brief
** cast ray from camera to x,y pos where x,y pixel position of our screen
*/
t_ray	cast_camera_ray(t_camera camera, float x, float y)
{

	t_ray	ray;
	float	px;
	float	py;

#if 0 //pinhole normalized camera
		//using angle of camera
	px = (2.0f * ((x + 0.5f) / DEFAULT_WIDTH) - 1.0f) * camera.angle * camera.ratio;
	py = (1.0f - 2.0f * (y + 0.5f) / DEFAULT_HEIGHT) * camera.angle;
	ray.origin = camera.origin;
	ray.direction = (float4)(px, py, 1.0f, 0.0f);
	ray.direction = normalize(ray.direction);

#elif 0 //ortographic projection
	px = 1.0f /*pixel_size*/ * (x - 0.5f * (DEFAULT_WIDTH));
	py = 1.0f * (-y + 0.5f * (DEFAULT_HEIGHT));
	ray.origin = (float4)(px, py, 100.0f, 0.0f);
	ray.direction = (float4)(0.0f, 0.0f, -1.0f, 0.0f);
#elif 1 //pinhole normalized camera
		//using distance between camera position and viewplane
	// ray.direction = (float4)(1.0f * (x - 0.5f * (DEFAULT_WIDTH - 1.0f)),
							// -1.0f * (y - 0.5f * (DEFAULT_HEIGHT - 1.0f)),
							// -300.0f, 0.0f);
	// px = -2.0f * camera.viewplane.pixel_size * (x - 0.5f * DEFAULT_WIDTH);
	// py = -2.0f * camera.viewplane.pixel_size * (y - 0.5f * DEFAULT_HEIGHT);
	px = (2.0f * ((x + 0.5f) / DEFAULT_WIDTH) - 1.0f) * camera.ratio;
	py = (1.0f - 2.0f * (y + 0.5f) / DEFAULT_HEIGHT);
	ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
	ray.origin = camera.origin;
	ray.direction = normalize(ray.direction);
	if (get_global_id(0) == 100)
	{
		printf("%f %f %f\n", camera.u.x, camera.u.y, camera.u.z);
		printf("%f %f %f\n", camera.v.x, camera.v.y, camera.v.z);
		printf("%f %f %f\n", camera.w.x, camera.w.y, camera.w.z);
	}
#endif
	return ray;
}
