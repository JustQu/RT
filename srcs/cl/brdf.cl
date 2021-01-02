/*
** BRDF - bidirectional reflectance distributuin functions

** the function f returns the BRDF itself, unless it contains the delta function
**
** the function sample_f is used to compute the direction of reflected rays for
** simulating reflective materials and diffuse-diffuse light transport
**
** the function rho returns the bihemispherical reflectance
*/

/*
** BRDF
** 	Lambertian
**	PerfectSpecular
** 	GlossySpecular
*/

t_color
f(t_shade_rec const shade_rec,
	t_material const material,
	float4 const wi, float4 const wo)
{
	if (material.type == matte)
	{
		;
	}
	else if (material.type == phong)
	{
		;
	}
	else
	{
		;
	}
}

t_color	sample_f();

t_color	rho();

t_color	lambertian_f(float kd, t_color color)
{
	return (float_color_multi(kd * M_1_PI_F, color));
}

t_color	lambertian_rho(float kd, t_color color)
{
	return (float_color_multi(kd, color));
}

t_color	glossy_specular_f(float4 camera_direction, float4 normal,
						float4 wi, float ndotwi,
						float ks, float exp)
{
	float l = 0.0f;
	/* get reflected ray */
	float4	r = -wi + 2.0f * normal * ndotwi;
	float	rdotdir = dot(r, camera_direction);

	if (rdotdir > 0.0f)
		l = ks * pow(rdotdir, exp);
	return ((t_color){ .r = l, .g = l, .b = l });
}

t_color	perfect_specular_f(float4 ray_dir, float4 normal, float kr, t_color cr)
{
	float	ndotwo = dot(normal, ray_dir);
	float4	wi = -ray_dir + 2.0f * normal * ndotwo;

	return (float_color_multi(kr / dot(normal, wi), cr));
}
