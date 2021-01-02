/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:02:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/04 12:47:17 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
** @brief Set the color using int value
**
** @param color
** @param value
** @return ** void
*/

void	set_color_int(t_color *color, int value)
{
	color->r = ((value >> 16) & 0x000000ff) / 255.f;
	color->g = ((value >> 8) & 0x000000ff) / 255.0f;
	color->b = (value & 0x000000ff) / 255.0f;
}

/*
** @brief Set the color using integer components
**
** @param color
** @param r
** @param g
** @param b
** @return ** void
*/

void	set_color_uchar(t_color *color, uint8_t r, uint8_t g, uint8_t b)
{
	color->r = r / 255.0f;
	color->b = b / 255.0f;
	color->g = g / 255.0f;
}

/*
** @brief Set the color using float normalized components
**
** @param color
** @param r
** @param g
** @param b
** @return ** void
*/

void	set_color_float(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
