/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:14:14 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:22:01 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**vec3 cross product
**this is just convenient wrapper
*/

void	cross(t_vec3 a, t_vec3 b, t_vec3 d)
{
	vec3_cross(a, b, d);
}

/*
**vec3 dot product
**this is just convenient wrapper
*/

float	dot(t_vec3 a, t_vec3 b)
{
	return (vec3_dot(a, b));
}

/*
**normalize vec3 and store result in same vec
**this is just convenient wrapper
*/

void	normalize(t_vec3 v)
{
	vec3_normalize(v);
}

/*
**normalize vec3 to dest
**this is just convenient wrapper
*/

void	normalize_to(t_vec3 v, t_vec3 dest)
{
	vec3_normalize_to(v, dest);
}
