/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:35:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:07:07 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_light_types			t_light_type;
typedef struct s_light				t_light;
typedef struct s_ambient_occluder	t_ambient_occluder;

enum	e_light_types
{
	light_none = -2,
	ambient = 0,
	ambient_occluder,
	directional,
	point,
	area,
	enviromental
};

/*
** struct for light object
** matrix - tranformation matrix for area lights
** origin - origin of point light
** direction - direction of directional light
** color - light color
** ls - radiance scaling factor [0, inf)
** type - type of the light
** object_id - id of object for area light
** pdf - area value for area light
*/

struct				s_light
{
	cl_float16		matrix;
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls;
	t_light_type	type;
	cl_int			object_id;
	cl_float		pdf;
};

/*
** ambient occluder for more realistic ambient illumination
** todo: delete u,v,w?
*/

struct				s_ambient_occluder
{
	cl_float4		u;
	cl_float4		v;
	cl_float4		w;
	t_color			color;
	t_color			min_amount;
	cl_float		ls;
	cl_int			sampler_id;
	cl_int			gap[2];
};

#endif
