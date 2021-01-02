/*
** old ver of interpolation for perlin noise
*/
float	trilinear_interp(float c[2][2][2], float u, float v, float w)
{
	float	accum = 0.0f;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				accum += (i * u + (1 - i) * (1 - u))
						* (j * v + (1 - j) * (1 - v))
						* (k * w + (1 - k) * (1 - w))
						* c[i][j][k];
	return accum;
}

float	perlin_interp(float3 c[2][2][2], float u, float v, float w)
{
	float	uu = u * u * (3.0 - 2.0 * u);
	float	vv = v * v * (3.0 - 2.0 * v);
	float	ww = w * w * (3.0 - 2.0 * w);
	float	accum = 0.0f;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				// float3 weight_v = (float3)(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu))
						* (j * vv + (1 - j) * (1 - vv))
						* (k * ww + (1 - k) * (1 - ww))
						* dot(c[i][j][k], (float3)(u - i, v - j, w - k));
			}
	return (accum);
}

float	perlin_noise(__global float4 *perlin_noise,
					__global int *perm_x,
					__global int *perm_y,
					__global int *perm_z,
					float4 point)
{
	float	u = point.x - floor(point.x);
	float	v = point.y - floor(point.y);
	float	w = point.z - floor(point.z);
	u = u * u * (3.0 - 2.0 * u);
	v = v * v * (3.0 - 2.0 * v);
	w = w * w * (3.0 - 2.0 * w);
	int		i = (int)(4.0f * point.x) & 255;
	int		j = (int)(4.0f * point.y) & 255;
	int		k = (int)(4.0f * point.z) & 255;
	return (perlin_noise[perm_x[i] ^ perm_y[j] ^ perm_z[k]].w);
}

float	smooth_perlin_noise(__global float4 *ranvec,
							__global int *perm_x,
							__global int *perm_y,
							__global int *perm_z,
							float4 point)
{
	int		i = floor(point.x);
	int		j = floor(point.y);
	int		k = floor(point.z);
	float	u = point.x - i;
	float	v = point.y - j;
	float	w = point.z - k;

	float3	c[2][2][2];
	for (int di = 0; di < 2; di++)
		for (int dj = 0; dj < 2; dj++)
			for (int dk = 0; dk < 2; dk++)
				c[di][dj][dk] = ranvec[perm_x[(i + di) & 255]
										^ perm_y[(j + dj) & 255]
										^ perm_z[(k + dk) & 255]].xyz;
	return (perlin_interp(c, u, v, w));
}

float	turbulence_perlin_noise(__global float4 *ranvec,
								__global int *perm_x,
								__global int *perm_y,
								__global int *perm_z,
								float4 point)
{
	float	accum = 0.0f;
	float4	temp_p = point;
	float	weight = 1.0f;
	for (int i = 0; i < 7; i++) {
		accum += weight * smooth_perlin_noise(ranvec, perm_x, perm_y, perm_z, temp_p);
		weight *= 0.5f;
		temp_p *= 2.0f;
	}
	return fabs(accum);
}
