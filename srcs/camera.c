/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 01:05:19 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:18:31 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vector.h"
#include "matrix.h"

void	compute_uvw(t_camera *camera)
{
	camera->w.x = -camera->direction.x;
	camera->w.y = -camera->direction.y;
	camera->w.z = -camera->direction.z;
	camera->w.w = 0.0f;
	camera->w = norm4(camera->w);
	if (camera->w.y < 0.9f)
		camera->u = cross_product(UP, camera->w);
	else
		camera->u = cross_product(RIGHT, camera->w);
	camera->u.x = -camera->u.x;
	camera->u.y = -camera->u.y;
	camera->u.z = -camera->u.z;
	camera->v = cross_product(camera->w, camera->u);
	camera->v.x = -camera->v.x;
	camera->v.y = -camera->v.y;
	camera->v.z = -camera->v.z;
}

void	move_camera(t_camera *camera, int direction, float step)
{
	if (direction == 0)
	{
		camera->origin.x += camera->u.x * step;
		camera->origin.y += camera->u.y * step;
		camera->origin.z += camera->u.z * step;
	}
	else if (direction == 1)
	{
		camera->origin.x += camera->v.x * step;
		camera->origin.y += camera->v.y * step;
		camera->origin.z += camera->v.z * step;
	}
	else
	{
		camera->origin.x += camera->w.x * step;
		camera->origin.y += camera->w.y * step;
		camera->origin.z += camera->w.z * step;
	}
}

/*
** @brief
**
** @param camera
** @param axis 0 - x, 1 - y, 2 - z
** @param angle_degrees
** @return ** void
*/

void	rotate_camera(t_camera *camera, int axis, float angle_degrees)
{
	t_matrix	m;

	if (axis == 0)
	{
		m = rotate_about_axis(camera->u, angle_degrees * (float)M_PI / 180.0f);
		camera->u = norm4(vector_matrix_mul(camera->u, m));
		camera->v = norm4(vector_matrix_mul(camera->v, m));
		camera->w = norm4(vector_matrix_mul(camera->w, m));
	}
	else if (axis == 1)
	{
		m = rotate_about_axis(camera->v, angle_degrees * (float)M_PI / 180.0f);
		camera->u = norm4(vector_matrix_mul(camera->u, m));
		camera->v = norm4(vector_matrix_mul(camera->v, m));
		camera->w = norm4(vector_matrix_mul(camera->w, m));
	}
	else
	{
		m = rotate_about_axis(camera->w, angle_degrees * (float)M_PI / 180.0f);
		camera->u = norm4(vector_matrix_mul(camera->u, m));
		camera->v = norm4(vector_matrix_mul(camera->v, m));
		camera->w = norm4(vector_matrix_mul(camera->w, m));
	}
}
