/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:37:46 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/20 22:17:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LEGACY_BVH_01_H
# define RT_LEGACY_BVH_01_H

# include "bvh.h"

int		cmp_x(t_bvh_node a, t_bvh_node b);
int		cmp_y(t_bvh_node a, t_bvh_node b);
int		cmp_z(t_bvh_node a, t_bvh_node b);

#endif
