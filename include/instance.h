/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 20:05:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:38:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_H
# define INSTANCE_H

# ifndef __OPENCL_C_VERSION__
#  include "material.h"
#  include "objects.h"
# endif

/*
** 96 bytes
*/

typedef struct s_instance	t_instance;

/*
** @brief
** object_id = triangle_id if type == triangle
** todo: remove matrix manager
*/

struct	s_instance
{
	t_material			material;

	cl_int				object_id;
	cl_int				matrix_id;
	t_type				type;
	cl_float			area;
	cl_int				gap[3];
	cl_uchar			uchar_gap[3];
	cl_uchar			shadows;
};

#endif
