
float	GPURnd(float4 *state)
{
	float4 q = (float4)(1225.0f, 1585.0f, 2457.0f, 2098.0f);
	float4 r = (float4)(1112.0f, 367.0f, 92.0f, 265.0f);
	float4 a = (float4)(3423.0f, 2646.0f, 1707.0f, 1999.0f);
	float4 m = (float4)(4194287.0f, 4194277.0f, 4194191.0f, 4194167.0f);

	float4 state_copy = *state;
	float4 beta = floor(state_copy / q);
	float4 p = a * (state_copy - beta * q) - beta * r;
	beta = (sign(-p) + (float4)(1.0f)) * (float4)(0.5f) * m;
	state_copy = p + beta;

	*state = state_copy;
	float res;
	return fract(dot(state_copy / m, (float4)(1.0f, -1.0f, 1.0f, -1.0f)), &res);
}

float4	random_cosine_direction(float4 *state)
{
	float r2 = GPURnd(state);
	float z = sqrt(1.0f - r2);
	float r1 = GPURnd(state);
	float phi = 2.0f * M_PI * r1;
	float x = cos(phi) * 2.0f * sqrt(r2);
	float y = sin(phi) * 2.0f * sqrt(r2);
	return (float4)(x, y, z, 0.0f);
}


/**
** todo: add to material fuzz
*/
bool	metal_scatter(t_texture_manager texture_manager,
					t_material material,
					t_shade_rec *shade_rec,
					t_color *attenuation,
					float4 *state)
{
	shade_rec->normal = dot(shade_rec->normal, shade_rec->ray.direction) < 0.0f ?
							shade_rec->normal : -shade_rec->normal;
	float4 reflected = get_reflected_vector(shade_rec->ray.direction, shade_rec->normal);

	shade_rec->ray.origin = shade_rec->hit_point + 0.1f * shade_rec->normal;
	shade_rec->ray.direction = reflected
							+ 0.3f * random_in_unit_sphere(state);

	*attenuation = float_color_multi(
						material.kr,
						get_color(texture_manager, material, shade_rec));
	// *attenuation = float_color_multi(material.kr, material.color);
	return (dot(reflected, shade_rec->normal) > 0.0f);
}

void	build_from_w(float4 *const u, float4 *const v, float4 *const w,
					float4 const n)
{
	float4 a;

	*w = n;
	if (fabs(w->x) > 0.9f)
		a = (float4)(0.0f, 1.0f, 0.0f, 0.0f);
	else
		a = (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	*v = normalize(cross(*w, a));
	*u = cross(*w, *v);
}

/* return normalized direcrtion in u,v,w coordinate system */
float4	local_dir(float4 const *const u,
				float4 const *const v,
				float4 const *const w,
				float4 const a)
{
	return normalize(a.x * *u + a.y * *v + a.z * *w);
}
