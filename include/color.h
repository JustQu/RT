/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:51:48 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/16 18:00:09 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

#include "types.h"

typedef union s_color	t_color;

union					s_color {
	cl_int				value;
	struct
	{
		cl_uchar		b;
		cl_uchar		g;
		cl_uchar		r;
		cl_uchar		a;
	};
};



#endif
