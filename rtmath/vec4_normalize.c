/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 23:58:15 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:11:13 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"
#include "math.h"

/*
**norm * norm(magnitude) of vec
*/

float	vec4_norm2(t_vec4 v)
{
	return (vec4_dot(v, v));
}

/*
**norm(magnitude) of vec4
*/

float	vec4_norm(t_vec4 v)
{
	return (sqrtf(vec4_dot(v, v)));
}

/*
**normalize vec4 to dest
*/

void	vec4_normalize_to(t_vec4 v, t_vec4 dest)
{
	float	norm;

	norm = vec4_norm(v);
	if (norm == 0.0f)
	{
		vec4_zero(dest);
		return ;
	}
	vec4_scale(v, 1.0f / norm, dest);
}

/*
**normalize vec4 and store result in same vec
*/

void	vec4_normalize(t_vec4 v)
{
	vec4_normalize_to(v, v);
}
