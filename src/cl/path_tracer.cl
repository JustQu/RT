// #include "cl_rt.h"

//С накоплением цвета проблемы. Что такое эмиссия? И не понятно что на что умножать
float3		path_tracing(t_ray camray,
						__constant t_obj *objects, int nobjects,
						__constant t_triangle *triangles, int ntriangles,
						__constant t_light *lights, int nlights,
						t_render_options options,
						unsigned int *seed0, unsigned int *seed1)
{
	t_ray	ray = camray;
	float3	accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3	mask = (float3)(1.0f, 1.0f, 1.0f);

	for (int bounces = 0; bounces < BOUNCES; bounces++)
	{
		t_shade_rec	shade_rec;

		// float	t;
		// int		hitobj_id = 0;

		if (!scene_intersection(ray, &shade_rec,
					objects, nobjects,
					triangles, ntriangles))
		// if (!intersect_scene(objects, ray, &t, &hitobj_id, nobjects))
			return accum_color += mask * (float3)(0.05f, 0.05f, 0.05f);

		t_obj	hit_obj = objects[shade_rec.id];

		/* compute the hitpoint using the ray equation */
		// float4	hitpoint = ray.origin + ray.direction * t;

		shade_rec.hit_point = (shade_rec.hit_info.t) * shade_rec.ray.direction + shade_rec.ray.origin;

		/* compute the surface normal and flip it if necessary to face the incoming ray */
		float4	normal = shade_rec.hit_a_triangle ?
							get_triangle_normal(triangles[shade_rec.id]) :
							get_object_normal(shade_rec.hit_point, objects[shade_rec.id], shade_rec.hit_info);
		float4 normal_facing = dot(normal, ray.direction) < 0.0f ? normal : -normal;

		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
		float rand1 = 2.0f * M_PI * get_random(seed0, seed1);
		float rand2 = get_random(seed0, seed1);
		float rand2s = sqrt(rand2);

		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float4 w = normal_facing;
		float4 axis = fabs(w.x) > 0.1f ? (float4)(0.0f, 1.0f, 0.0f, 0.0f) : (float4)(1.0f, 0.0f, 0.0f, 0.0f);
		float4 u = normalize(cross(axis, w));
		float4 v = cross(w, u);

		/* use the coordinte frame and random numbers to compute the next ray direction */
		float4 newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));

		/* add a very small offset to the hitpoint to prevent self intersection */
		// ray.origin = hitpoint + normal_facing * EPSILON;
		ray.origin = shade_rec.hit_point + normal_facing * EPSILON;
		ray.direction = newdir;

		/* add the colour and light contributions to the accumulated colour */
		// accum_color += mask * hit_obj.material.emission;

		/* the mask colour picks up surface colours at each bounce */
		// mask *= hit_obj.material.color;

		/* perform cosine-weighted importance sampling for diffuse surfaces*/
		mask *= dot(newdir, normal_facing);
	}

	return accum_color;
}
