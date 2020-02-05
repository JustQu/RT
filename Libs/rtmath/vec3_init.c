/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:01:44 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:22:50 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**init vec3 using vec4
*/

void	vec4_to_vec3(t_vec4 v4, t_vec3 dest)
{
	dest[0] = v4[0];
	dest[1] = v4[1];
	dest[2] = v4[2];
}

/*
**copy all members of [a] to [dest]
*/

void	vec3_copy(t_vec3 a, t_vec3 dest)
{
	dest[0] = a[0];
	dest[1] = a[1];
	dest[2] = a[2];
}

/*
**make vector zero
*/

void	vec3_zero(t_vec3 v)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

/*
**make vector one
*/

void	vec3_one(t_vec3 v)
{
	v[0] = 1.0f;
	v[1] = 1.0f;
	v[2] = 1.0f;
}

/*
**fill a vector with specified value
*/

void	vec3_broadcast(float val, t_vec3 d)
{
	d[0] = val;
	d[1] = val;
	d[2] = val;
}
