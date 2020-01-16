/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:44:14 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/16 11:34:07 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			put_pixel(Uint32 *img, int x, int y, int color)
{
	Uint32	pixpos;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	pixpos = y * SCREEN_WIDTH + x;
	img[pixpos] = color;
}

static void		reflect(t_vec3 i, t_vec3 n, t_vec3 dest)
{
	float	k;
	t_vec3	tmp;

	k = vec3_dot(i, n);
	vec3_scale(n, 2 * k, tmp);
	vec3_sub(i, tmp, dest);
}

static t_color	calc_color(t_obj *obj, float diff_light, float spec_light)
{
	t_color	color;

	color.bgra[0] = clamp(obj->mat.diff_color.bgra[0] * (diff_light *
						obj->mat.kd + spec_light * obj->mat.ks), 0, 255);
	color.bgra[1] = clamp(obj->mat.diff_color.bgra[1] * (diff_light *
						obj->mat.kd + spec_light * obj->mat.ks), 0, 255);
	color.bgra[2] = clamp(obj->mat.diff_color.bgra[2] * (diff_light *
						obj->mat.kd + spec_light * obj->mat.ks), 0, 255);
	color.bgra[3] = clamp(obj->mat.diff_color.bgra[3] * (diff_light *
						obj->mat.kd + spec_light * obj->mat.ks), 0, 255);
	return (color);
}

t_color			get_point_color(t_world *world, t_obj *obj, t_ray *ray, int i)
{
	t_vec3	ds_light;
	t_obj	*shadow_obj;
	t_vec3	r;
	t_vec4	light_dir;
	t_ray	shadow_ray;

	vec3_zero(ds_light);
	while (++i < world->nlights)
	{
		shadow_ray = cast_shadow_ray(obj->hit_point, world->lights + i);
		if ((shadow_obj = get_intersection(world->objs,
											world->nobjs, &shadow_ray)) != NULL)
			if (shadow_obj != obj &&
			vec3_distance(obj->hit_point, (world->lights + i)->c_s) >
				vec3_distance(obj->hit_point, shadow_obj->hit_point))
				continue;
		vec3_sub((world->lights + i)->c_s, obj->hit_point, light_dir);
		vec3_normalize(light_dir);
		ds_light[ox] += (world->lights + i)->intensity *
								max(0, vec3_dot(light_dir, obj->surf_normal));
		reflect(light_dir, obj->surf_normal, r);
		ds_light[oy] += (world->lights + i)->intensity *
								powf(max(0.0f, dot(r, ray->vec)), obj->mat.n);
	}
	return (calc_color(obj, ds_light[ox], ds_light[oy]));
}

void			render(t_param *p)
{
	t_ray	ray;
	t_vec2	iters;
	t_color	color;

	vec3_zero(ray.point);
	iters[oy] = -1;
	while (++iters[oy] < SCREEN_HEIGHT)
	{
		iters[ox] = -1;
		while (++iters[ox] < SCREEN_WIDTH)
		{
			vec4_copy((t_vec4){1, 1, 1, 1}, ray.vec);
			ray.vec[oy] = (1 - 2 * ((iters[oy] + 0.5) * p->camera.inv_h))
			* p->camera.angle;
			ray.vec[ox] = (2 * ((iters[ox] + 0.5) * p->camera.inv_w) - 1)
			* p->camera.angle * p->camera.ratio;
			normalize(ray.vec);
			color = trace_ray(p, &ray);
			put_pixel(p->img, iters[ox], iters[oy], color.color);
		}
	}
}
