__kernel void translate_image(__global float3 *float3_image,
							__global uint *uint_image,
							int num_samples)
{
	t_color	color;
	float3	rgb;
	int		global_id = get_global_id(0);

	rgb = float3_image[global_id];
	color.r = rgb.x / num_samples;
	color.g = rgb.y / num_samples;
	color.b = rgb.z / num_samples;

	uint_image[global_id] = color.value;
}
