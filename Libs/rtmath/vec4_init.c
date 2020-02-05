/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 23:55:20 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:11:30 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

/*
** init vec4 using vec3
*/

void	vec3_to_vec4(t_vec3 v3, float last, t_vec4 dest)
{
	dest[0] = v3[0];
	dest[1] = v3[1];
	dest[2] = v3[2];
	dest[3] = last;
}

/*
**fill a vectir with specified value
*/

void	vec4_broadcast(float val, t_vec4 d)
{
	d[0] = val;
	d[1] = val;
	d[2] = val;
	d[3] = val;
}

/*
**copy all members of [v] to dest
*/

void	vec4_copy(t_vec4 v, t_vec4 dest)
{
	dest[0] = v[0];
	dest[1] = v[1];
	dest[2] = v[2];
	dest[3] = v[3];
}

/*
**make vector zero
*/

void	vec4_zero(t_vec4 v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

/*
**make vector one
*/

void	vec4_one(t_vec4 v)
{
	v[0] = 1.0f;
	v[1] = 1.0f;
	v[2] = 1.0f;
	v[3] = 1.0f;
}
