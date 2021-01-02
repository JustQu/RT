// typedef union
// {
// 	struct
// 	{
// 		char b;
// 		char g;
// 		char r;
// 		char a;
// 	};
// 	int	value;
// }	int_color;

__kernel void translate_image(__global float4 *rgb_image,
							__global uchar4 *result_image,
							float num_samples)
{
	int				global_id = get_global_id(0);
	float4			color;

	color = rgb_image[global_id];
	// color = rgb_image[global_id] / num_samples;

	uchar4 old = result_image[global_id];

	float4 a;
	a.x = old.x / 255.99f;
	a.y = old.y / 255.99f;
	a.z = old.z / 255.99f;
	a.w = old.w / 255.99f;

	// float4 c = (a + color) / (num_samples + 1);
	// float4 c = mix(color, a, 0.5f);
	// float4 max_v = max(a, color);

	// uchar4 out = convert_uchar4_sat_rte(sqrt(c) * 255.00f);

	// if (global_id == 0)
	// 	printf("%v3f || %v3f || %v3f\n", a, color, c);
	uchar4 out = convert_uchar4_sat_rte(sqrt(color / (float)num_samples) * 255.99f);

	result_image[global_id] = out;
}
