
// #include "cl_rt.h"

t_ray cast_camera_ray(t_camera camera, float x, float y, t_sampler_manager sampler_manager,
					t_sampler *camera_sampler, uint2 *seed)
{
	t_ray	ray;
	float	px;
	float	py;
	float	pixel_size;

	pixel_size = camera.viewplane.pixel_size / camera.zoom;
	if (camera.normalized == true)
	{
		px = pixel_size * ((2.0f * x / camera.viewplane.width) - 1.0f);
		py = pixel_size * (1.0f - 2.0f * y / DEFAULT_HEIGHT) / camera.viewplane.width * camera.viewplane.height;
	}
	else
	{
		px = pixel_size * (x - 0.5f * camera.viewplane.width);
		py = pixel_size * (0.5f * camera.viewplane.height - y) / camera.ratio;
	}

	if (camera.type == perspective)
	{
		ray.origin = camera.origin;
		ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == thin_lens)
	{
		float2 dp = sample_unit_disk(camera_sampler, sampler_manager.disk_samples, seed);
		float2 lp = dp * camera.lens_radius; //lens_point
		ray.origin = camera.origin + camera.u * lp.x + camera.v * lp.y;
		px = px * camera.f / camera.d;
		py = py * camera.f / camera.d;
		ray.direction = (px - lp.x) * camera.u + (py - lp.y) * camera.v - camera.w * camera.f;
		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == fisheye)
	{
		float2 sp = sample_unit_square(camera_sampler, sampler_manager.samplers, seed);
	}
	return (ray);
}
