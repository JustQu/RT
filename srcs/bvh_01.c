/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:30:35 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/14 10:30:37 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int		cmp_x(t_bvh_node a, t_bvh_node b)
{
	return (a.center.x < b.center.x);
}

int		cmp_y(t_bvh_node a, t_bvh_node b)
{
	return (a.center.y < b.center.y);
}

int		cmp_z(t_bvh_node a, t_bvh_node b)
{
	return (a.center.z < b.center.z);
}
