/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:19:57 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 18:11:47 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		move_obj_to_camera(t_obj *obj, t_camera *camera)
{
	vec3_copy(obj->origin, obj->c_s);
	vec3_sub(obj->c_s, camera->origin, obj->c_s);
}

void		world_to_camera(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->world.nobjs)
	{
		vec3_copy((p->world.objs + i)->origin, (p->world.objs + i)->c_s);
		vec3_sub((p->world.objs + i)->c_s,
		p->camera.origin, (p->world.objs + i)->c_s);
	}
	i = -1;
	while (++i < p->world.nlights)
	{
		vec3_copy((p->world.lights + i)->origin, (p->world.lights + i)->c_s);
		vec3_sub((p->world.lights + i)->c_s,
		p->camera.origin, (p->world.lights + i)->c_s);
	}
	vec3_zero(p->camera.origin);
}

static void	rot_obj_to_cam(t_vec3 c_s, t_vec3 rot_mat)
{
	t_vec3	rot;

	if (rot_mat[oy] != 0)
	{
		rot[ox] = cos(rot_mat[oy]) * c_s[ox] + sin(rot_mat[oy]) * c_s[oz];
		rot[oz] = -sin(rot_mat[oy]) * c_s[ox] + cos(rot_mat[oy]) * c_s[oz];
		c_s[ox] = rot[ox];
		c_s[oz] = rot[oz];
	}
	if (rot_mat[ox] != 0)
	{
		rot[oy] = cos(rot_mat[ox]) * c_s[oy] + sin(rot_mat[ox]) * c_s[oz];
		rot[oz] = -sin(rot_mat[ox]) * c_s[oy] + cos(rot_mat[ox]) * c_s[oz];
		c_s[oy] = rot[oy];
		c_s[oz] = rot[oz];
	}
	if (rot_mat[oz] != 0)
	{
		rot[ox] = cos(rot_mat[oz]) * c_s[ox] - sin(rot_mat[oz]) * c_s[oy];
		rot[oy] = sin(rot_mat[oz]) * c_s[ox] + cos(rot_mat[oz]) * c_s[oy];
		c_s[ox] = rot[ox];
		c_s[oy] = rot[oy];
	}
}

void		rotate_camera(t_param *p)
{
	t_vec3	cam_rot;
	int		i;

	i = -1;
	vec3_copy(p->camera.orient, cam_rot);
	cam_rot[ox] *= -1.0f;
	cam_rot[oy] *= -1.0f;
	cam_rot[oz] *= -1.0f;
	while (++i < p->world.nobjs)
	{
		rot_obj_to_cam(p->world.objs[i].c_s, cam_rot);
		if (p->world.objs[i].type == cone)
			rot_obj_to_cam(((t_cone *)p->world.objs[i].data)->dir, cam_rot);
		else if (p->world.objs[i].type == plane)
			rot_obj_to_cam(((t_plane *)p->world.objs[i].data)->nv, cam_rot);
		else if (p->world.objs[i].type == cylinder)
			rot_obj_to_cam(((t_cylinder *)p->world.objs[i].data)->dir,
			cam_rot);
	}
	i = -1;
	while (++i < p->world.nlights)
	{
		rot_obj_to_cam(((p->world.lights[i]).c_s), cam_rot);
	}
}
