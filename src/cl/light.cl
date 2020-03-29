// #include "world.h"
// #include "cl_rt.h"

t_color
lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * (float)M_1_PI, color));
}

float	glossy_specular_f(float4 camera_direction, float4 normal, float4 light_direction, float ks, float exp)
{
	float	res = 0;
	float4	r = get_reflected_vector(light_direction, normal);
	float	rdotdir = dot(r, camera_direction);

	if (rdotdir > 0)
		res = ks * pow(rdotdir, exp);
	return res;
}

 t_color	lambertian_rho(float kd, t_color color)
{
	t_color	res;

	res = float_color_multi(kd, color);
	return (res);
}

 float4	get_light_direction(t_light light, t_shade_rec shade_rec)
{
	if (light.type == ambient)
		return ((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	else if (light.type == point)
		return (normalize(light.origin - shade_rec.hit_point));
	else if (light.type == directional)
		return -normalize(light.direction);
}

 t_color	get_light_radiance(t_light light)
{
	t_color	color;

	if (light.type == ambient)
	{
		color.r = clamp(light.color.r * light.ls, 0.0f, 255.0f);
		color.g = clamp(light.color.g * light.ls, 0.0f, 255.0f);
		color.b = clamp(light.color.b * light.ls, 0.0f, 255.0f);
		return (color);
	}
}
