/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:46:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:47:36 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
# endif

typedef enum e_camera_type	t_camera_type;

/*
** 160 bytes
*/

typedef struct s_camera		t_camera;
typedef struct s_viewplane	t_viewplane;

# define UP (cl_float4){{0.0f, 1.0f, 0.0f, 0.0f}}
# define RIGHT (cl_float4) {{1.0f, 0.0f, 0.0f, 0.0f}}

/*
** @brief Набор типов камеры
**
** orthographic - ортографическая проекция
** perspective - перспектива
** thin_lens - эффект тонкой линзы
** fisheye - эффект рыбьего глаза
** spherical - сферическая проекция
** stereo - стерео изображение
*/

enum				e_camera_type
{
	cam_none = -2,
	orthographic = 0,
	perspective,
	thin_lens,
	fisheye,
	spherical,
	stereo
};

/*
** @brief Плоскость проецирования
** pixel_size - размер пикселя, по умолчанию 1
** width - ширина плоскости
** height - высота плоскости
*/

struct	s_viewplane
{
	cl_float		pixel_size;
	cl_int			width;
	cl_int			height;
};

/*
** @brief Класс камеры
**
** viewplane - плоскоть проецирования
** origin - местоположение камеры
** direction - напралвние взгляда
** u, v, w - внутренняя система координат камеры
** d - расстояние до viewplane, плоскости проецирования
** zoom - коэффициент приближения
** exposure_time - экспозиция
** type - тип камеры
** sampler_id - идентификатор сэмплера для тонкой линзы
** normalized - флаг cостояния, указывающий на нормализованные координаты
** l - Радиус тонкой линзы, либо коэффициент в сферической камере,
**     либо расстояние между изображениями в стерео камере
** f - расстояние до фокальной плоскости тонкой линзы,
**     либо максимальное угловое поле в рыбьем глазе.
*/

struct	s_camera
{
	cl_float4		origin;
	cl_float4		direction;
	cl_float4		up;
	cl_float4		u;
	cl_float4		v;
	cl_float4		w;
	t_viewplane		viewplane;
	cl_float		d;
	cl_float		zoom;
	cl_float		exposure_time;
	t_camera_type	type;
	cl_int			sampler_id;
	cl_int			normalized;
	cl_float		l;
	cl_float		f;
};

/*
** Setting up camera local coordinate system
*/

void	compute_uvw(t_camera *camera);

/*
** @brief rotate camera around local axis on some degrees
**
** @param camera
** @param axis 0 - x, 1 - y, 2 - z
** @param angle_degrees
** @return ** void
*/

void	rotate_camera(t_camera *camera, int axis, float angle_degrees);

/*
** @brief move camera in one of three local directions
**
** @param camera
** @param direction 0 - x; 1 - y; 2 - z
** @param step
** @return ** void
*/

void	move_camera(t_camera *camera, int direction, float step);

#endif
