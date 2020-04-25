
// #include "cl_rt.h"

t_ray cast_camera_ray(t_camera camera, float x, float y,
					t_sampler_manager sampler_manager, uint2 *seed)
{
	t_ray	ray;
	float	px;
	float	py;
	float	pixel_size;

	pixel_size = camera.viewplane.pixel_size / camera.zoom;
	if (camera.type == orthographic) //I think we can get rid of that
	{
		px = pixel_size * (x - 0.5f * camera.viewplane.width);
		py = -pixel_size * (y - 0.5f * camera.viewplane.height);
		ray.origin = (float4)(px, py, 100.0f, 0.0f) + camera.origin;
		ray.direction = (float4)(0.0f, 0.0f, -1.0f, 0.0f);
	}
	else if (camera.type == perspective)
	{
		px =  camera.viewplane.pixel_size * (x - 0.5f * DEFAULT_WIDTH);
		py = -camera.viewplane.pixel_size * (y - 0.5f * DEFAULT_HEIGHT) / camera.viewplane.width *camera.viewplane.height;
		// px = pixel_size * ((2.0f * x / DEFAULT_WIDTH) - 1.0f) * camera.ratio;
		// py = pixel_size * (1.0f - 2.0f * y / DEFAULT_HEIGHT);

		// px =  camera.viewplane.pixel_size * (x - 0.5f * DEFAULT_WIDTH);
		// py = -camera.viewplane.pixel_size * (y - 0.5f * DEFAULT_HEIGHT);

		ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
		ray.origin = camera.origin;

		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == thin_lens)
	{
		t_sampler sampler = get_sampler(sampler_manager, camera.sampler_id);
		sampler.count = 0;

		px =  camera.viewplane.pixel_size * (x - 0.5f * DEFAULT_WIDTH) ;
		py = -camera.viewplane.pixel_size * (y - 0.5f * DEFAULT_HEIGHT) / camera.viewplane.width * camera.viewplane.height;
		// px = pixel_size * ((2.0f * x / DEFAULT_WIDTH) - 1.0f) * camera.ratio;
		// py = pixel_size * (1.0f - 2.0f * y / DEFAULT_HEIGHT);

		float2 dp = sample_unit_disk(&sampler, sampler_manager.disk_samples, seed);

		float2 lp = dp * camera.lens_radius; //lens_point

		ray.origin = camera.origin + camera.u * lp.x + camera.v * lp.y;

		px = px * camera.f / camera.d;
		py = py * camera.f / camera.d;
		ray.direction = (px - lp.x) * camera.u + (py - lp.y) * camera.v - camera.w * camera.f;
		ray.direction = normalize(ray.direction);
	}
	return (ray);
}

/**
** @brief
** cast ray from camera to x,y pos where x,y pixel position of our screen
*/
t_ray	OLD_cast_camera_ray(t_camera camera, float x, float y)
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
#endif
	return ray;
}
