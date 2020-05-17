/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:35:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/16 19:59:14 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "objects.h"

typedef enum e_light_types			t_light_type;
typedef struct s_light				t_light;
typedef struct s_ambient_occluder	t_ambient_occluder;

//NOTE: some types will be removed from that list
enum	e_light_types
{
	ambient,
	ambient_occluder,
	directional,
	point,
	area,
	enviromental
};

#ifdef _WIN64
__declspec(align(4))
#endif
struct				s_light
{
	cl_float4		origin;
	cl_float4		direction;
	t_color			color;
	cl_float		ls; //radiance scaling factor [0, inf)
	t_light_type	type;

	cl_int			object_id; //for area lights
};

#ifdef _WIN64
__declspec(align(4))
#endif
struct				s_ambient_occluder
{
	cl_float4		u;
	cl_float4		v;
	cl_float4		w;
	t_color			color;
	cl_float		ls; //radiance scaling factor [0, inf)
	cl_int			sampler_id;
	t_color			min_amount;
};

#endif
