/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:46:35 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/16 17:59:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "types.h"

typedef enum e_camera_type			t_camera_type;
typedef struct s_camera				t_camera;
typedef struct s_viewplane			t_viewplane;

enum	e_camera_type
{
		orthographic,
		perspective,
		thin_lens,
		fisheye,
		spherical,
		stereo
};

# ifdef _WIN64
__declspec(align(4))
# endif
struct	s_viewplane
{
	cl_float	pixel_size;
	cl_int		width;
	cl_int		height;
};

/**
** @TODO: make transformation matrix
** TODO: singularity paragraph 9.9
*/
# ifdef _WIN64
__declspec(align(4))
# endif
struct	s_camera
{
	t_viewplane			viewplane;
	cl_float4			origin; // eye
	cl_float4			direction; // lookat - eye
	cl_float4			up; // (0, 1, 0)
	cl_float4			u;
	cl_float4			v; // actually we need only th3 vectors. the up vector could be hardcodeded and w = -direction
	cl_float4			w;
	cl_float			d; //the view-plane distance
	cl_float			zoom; //zoom factor
	cl_float			exposure_time; //using somewhere later
	t_camera_type		type;
	cl_int				sampler_id; //thin_camera
	cl_int				normalized;
	//thin-lens camera
	cl_float			l; //lens radius or lambda
	cl_float			f; //focal plane distance or psi_max in fisheye

//note: prob not needed
	cl_float			ratio;
	cl_float			inv_w;
	cl_float			inv_h;
	cl_float			angle;
	cl_int				fov;
};


#endif
