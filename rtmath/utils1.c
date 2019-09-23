/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 00:21:38 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:21:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
**multiply given parameter with itself = x * x or powf(x, 2)
*/

float	pow2(float x)
{
	return (x * x);
}

/*
**find minimum of given two values
*/

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
**find maximum of given two values
*/

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
**clamp a number between min and max
*/

float	clamp(float val, float min_val, float max_val)
{
	return (min(max(val, min_val), max_val));
}

/*
**clamp a number to zero and one
*/

float	clamp_zo(float val)
{
	return (clamp(val, 0.0f, 1.0f));
}
