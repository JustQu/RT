/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:04:16 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:19:07 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

/*
**substract b vector from a vector store result in dest (d = a - b)
*/

void	vec4_sub(t_vec4 a, t_vec4 b, t_vec4 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	dest[3] = a[3] - b[3];
}

/*
**substract scalar from v vector sore result in dest (d = v - vec(s))
*/

void	vec4_subs(t_vec4 v, float s, t_vec4 dest)
{
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
	dest[3] = v[3] - s;
}

/*
**negate vector components and store result in dest
*/

void	vec4_negate_to(t_vec4 v, t_vec4 dest)
{
	dest[0] = -v[0];
	dest[1] = -v[1];
	dest[2] = -v[2];
	dest[3] = -v[3];
}

/*
**flip sign of all vec4 members
*/

void	vec4_negate(t_vec4 v)
{
	vec4_negate_to(v, v);
}
