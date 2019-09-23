/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:15:35 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:20:58 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
**add scalar to v vector store result in dest (d = v + s)
*/

void	vec3_adds(t_vec3 v, float s, t_vec3 dest)
{
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
}

/*
**add a vector to b vector store result in dest
*/

void	vec3_sum(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
}
