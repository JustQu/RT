/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:22:35 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:12:46 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** convert degree to radians
*/

float	deg_to_rad(float deg)
{
	return (deg * RTM_PI / 180.0f);
}

/*
** convert radians to degree
*/

float	rad_to_deg(float rad)
{
	return (rad * 180.0f / RTM_PI);
}
