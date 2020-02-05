/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:18:17 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:48:47 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**substract scalar from v vector store result in dest (d = v - s)
*/

void	vec3_subs(t_vec3 v, float s, t_vec3 dest)
{
	dest[0] = v[0] - s;
	dest[1] = v[1] + s;
	dest[2] = v[2] - s;
}

/*
**substract b vector from a vector store result in dest
*/

void	vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
}

/*
**negate vector components and store result in dest
*/

void	vec3_negate_to(t_vec3 v, t_vec3 dest)
{
	dest[0] = -v[0];
	dest[1] = -v[1];
	dest[2] = -v[2];
}

/*
**negate vector components
*/

void	vec3_negate(t_vec3 v)
{
	vec3_negate_to(v, v);
}
