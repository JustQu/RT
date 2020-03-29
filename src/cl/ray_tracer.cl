// #include "cl_rt.h"

 float4	get_reflected_vector(float4 l, float4 n)
{
	float4	r;

	r = -l + 2 * dot(l, n) * n;
	return normalize(r);
}

 bool	shadow_hit_object(t_ray shadow_ray, t_obj obj, t_hit_info *hit_info)
{
	if (!obj.shadows)
		return false;
	return (is_intersect(shadow_ray, obj, hit_info));
}

//TODO: triangles
 bool	shadow_hit(t_light light, t_ray shadow_ray, t_shade_rec shade_rec, __constant t_obj *objects, int nobjects, __constant t_triangle *triangles, int ntriangles)
{
	float	t;
	float	d = distance(light.origin, shadow_ray.origin);

	for (int i = 0; i < nobjects; i++)
	{
		if (shadow_hit_object(shadow_ray, objects[i], &shade_rec.hit_info) &&
			shade_rec.hit_info.t < d)
			return (true);
	}
	return (false);
}

/*
lights can optionally cast shadows
objects can optionally cast shadows
materials can optionally cast shadows
*/
//TODO(dmelessa): light colors
//note we don't need an object. We should pass only material nad compute normal
//in function before
 t_color		shade_object(t_material material, t_shade_rec shade_rec,
	__constant t_light *lights, int nlights, t_light ambient_light,
	__constant t_obj *objects, int nobjects,
	__constant t_triangle *triangles, int ntriangles,
	t_render_options options)
{
	float4	normal;
	float4	light_direction;
	float	dirdotn;
	t_color	color_tmp;
	t_color	color;

	//revert camera ray for specular light
	// return material.color;
	shade_rec.ray.direction = -shade_rec.ray.direction;

	//compute ambient light using ka coefficent of the materail
	color = float_color_multi(ambient_light.ls,
					lambertian_rho(material.ka, material.color));

	//compute sahding for each light source
	for (int i = 0; i < nlights; i++)
	{
		bool	in_shadow = false;

		//compute light direction at hit point
		light_direction = get_light_direction(lights[i], shade_rec);

		//multiplying by 0.999f to avoid self shadowing error
		t_ray	shadow_ray = {.origin = shade_rec.hit_point * 0.999f, .direction = light_direction };

		if (options.shadows)
			in_shadow = shadow_hit(lights[i], shadow_ray, shade_rec, objects, nobjects, triangles, ntriangles);

		if (!in_shadow)
		{
			//compute angle between normal at the hit point and light direction
			dirdotn = dot(shade_rec.normal, light_direction);

			//if angle > 0 then hit point is receivingl light
			if (dirdotn > 0.0f)
			{
				//compute glossy_specular coefficient
				float a = glossy_specular_f(shade_rec.ray.direction, shade_rec.normal, light_direction, material.ks, material.exp) ;

				//compute lambertian color
				color_tmp = lambertian_f(material.kd, material.color);

				//sum lambertian color and glossy specular color
				color_tmp = color_sum(color_tmp, float_color_multi(a, (t_color){.value=0x00ffffff}));

				//compute how much light the point receives depends on angle between the normal at this point and 	light direction
				color_tmp = float_color_multi(lights[i].ls * (dirdotn), color_tmp);
				color = color_sum(color_tmp, color);
			}
		}
	}
	return (color);
}

//TODO(dmelessa): shading both sides of surface §14
 bool	scene_intersection(t_ray ray, t_shade_rec *shade_rec,
					 __constant t_obj *objects, int nobjects,
					 __constant t_triangle *triangles, int ntriangles)
{
	float		t;
	t_hit_info	last_rec;

	last_rec.t = K_HUGE_VALUE;
	shade_rec->hit_an_object = false;
	shade_rec->hit_a_triangle = false;
	for (int i = 0; i < nobjects; i++)
	{
		if (is_intersect(ray, objects[i], &shade_rec->hit_info) &&
			shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_an_object = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	for (int i = 0; i < ntriangles; i++)
	{
		if (triangle_intersection(ray, triangles[i], &shade_rec->hit_info) &&
			shade_rec->hit_info.t < last_rec.t)
		{
			shade_rec->hit_a_triangle = true;
			last_rec = shade_rec->hit_info;
			shade_rec->id = i;
		}
	}
	shade_rec->hit_info = last_rec;
	return (shade_rec->hit_an_object || shade_rec->hit_a_triangle);
}


//todo: move normal computation to ray_trace_function
t_color	ray_trace(t_ray ray, __constant t_obj *objects, int nobjects,
					__constant t_triangle *triangles, int ntriangles,
					__constant t_light *lights, int nlights,
					t_light ambient_light,
					t_render_options options)
{
	t_shade_rec	shade_rec;
	t_color		color;

	color.value = 0x000000af;
	if (scene_intersection(ray, &shade_rec, objects, nobjects,
			triangles, ntriangles))
		{
			shade_rec.ray = ray;	//for specular reflection
			shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction
				+ shade_rec.ray.origin;
			if (shade_rec.hit_a_triangle)
			{
				shade_rec.normal = get_triangle_normal(triangles[shade_rec.id]);
				color = shade_object(triangles[shade_rec.id].material, shade_rec,
									lights, nlights, ambient_light,
									objects, nobjects, triangles, ntriangles, options);
			}
			else
			{
				shade_rec.normal = get_object_normal(shade_rec.hit_point,
					objects[shade_rec.id], shade_rec.hit_info);
				shade_rec.normal = dot(shade_rec.normal, ray.direction) < 0.0f ?
					shade_rec.normal : -shade_rec.normal;
				color = shade_object(objects[shade_rec.id].material,
									shade_rec, lights, nlights,	ambient_light,
									objects, nobjects, triangles, ntriangles, options);
			}
		}
	return (color);
}
