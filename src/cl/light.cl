// #include "world.h"
// #include "cl_rt.h"

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
