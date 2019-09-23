/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:21:16 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/13 16:34:51 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "rt_types.h"

float	pow2(float x);
float	min(float a, float b);
float	max(float a, float b);
float	clamp(float val, float min_val, float max_val);
float	clamp_zo(float val);
float	deg_to_rad(float deg);
float	rad_to_deg(float rad);

#endif
