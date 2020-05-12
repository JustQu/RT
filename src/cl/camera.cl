
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
		py = pixel_size * (1.0f - 2.0f * y / camera.viewplane.height);
	}
	else
	{
		px = pixel_size * (x - 0.5f * camera.viewplane.width);
		py = pixel_size * (0.5f * camera.viewplane.height - y) ;
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
		float2 lp = dp * camera.l; //lens_point
		ray.origin = camera.origin + camera.u * lp.x + camera.v * lp.y;
		px = px * camera.f / camera.d;
		py = py * camera.f / camera.d;
		ray.direction = (px - lp.x) * camera.u + (py - lp.y) * camera.v - camera.w * camera.f;
		ray.direction = normalize(ray.direction);
	}
	else if (camera.type == fisheye)
	{
		ray.origin = camera.origin;

		float	r_squared = px * px + py * py;
		if (r_squared <= 1.0f)
		{
			float r = sqrt(r_squared);
			float psi = r * camera.f * 0.0174532925199432957; // PI / 180 todo: make define
			float sin_psi = sin(psi);
			float cos_psi = cos(psi);
			float sin_alpha = py / r;
			float cos_alpha = px / r;

			ray.direction = sin_psi * cos_alpha * camera.u + sin_psi * sin_alpha * camera.v - cos_psi * camera.w;
		}
		else
			ray.direction = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (camera.type == spherical)
	{
		ray.origin = camera.origin;

		//compute the angles lambda and phi in radians
		float	lambda = px * camera.l * 0.0174532925199432957;
		float	psi = py * camera.f * 0.0174532925199432957;

		//compute the spherical azimuth and polar angles

		float	phi = M_PI - lambda;
		float	theta = 0.5f * M_PI - psi;

		float	sin_phi = sin(phi);
		float	cos_phi = cos(phi);
		float	sin_theta = sin(theta);
		float	cos_theta = cos(theta);

		ray.direction = sin_theta * sin_phi * camera.u + cos_theta * camera.v + sin_theta * cos_phi * camera.w;
	}
	else if (camera.type == stereo) //todo: rewrite paragraph 12
	{
		float r = 10;
		float xx = r * tan(0.5f * camera.f * 0.0174532925199432957);

		if (x < (camera.viewplane.width) / 2.0f - camera.l) //right eye
		{
			px = px + camera.viewplane.width / 4;
			ray.origin = camera.origin + xx * camera.u;
			px = px - xx;
		}
		else if (x > (camera.viewplane.width) / 2.0f + camera.l) //left eye
		{
			px = px - camera.viewplane.width / 4;
			ray.origin = camera.origin - xx * camera.u;
			px = px + xx;
		}
		else
		{
			ray.direction = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
			return (ray);
		}
		ray.direction = px * camera.u + py  * camera.v - camera.d * camera.w; // camera coordinates
		ray.direction = normalize(ray.direction);
	}
	return (ray);
}
