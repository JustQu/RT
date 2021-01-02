/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 11:49:18 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# ifndef __OPENCL_C_VERSION__
#  include "rt_types.h"
#  include "color.h"
# endif

typedef enum e_material_type		t_material_type;

/*
** 64 bytes
*/

typedef struct s_material			t_material;

enum	e_material_type
{
	mat_none = -2,
	matte = 0,
	phong,

	plastic,

	emissive,
	diffuse_light,

	reflective,
	mirror,
	metal,
	conductor,

	dielectric,
	rough_dielectric,
};

/*
** color					//16
** reflective color 		//16
** type						//4
** kd						//4 -- diffuse
** ka						//4 -- ambient
** ks						//4 -- specular
** kr						//4 -- reflective
** kt						//4 -- tranpsarente
** exp						//4
** uchar is_reflective		//1
** uchar is_transparent		//1
**
** uchar gap[8]				//8
*/

struct	s_material
{
	t_color				reflective_color;
	t_material_type		type;
	cl_float			kd;
	cl_float			ka;
	cl_float			ks;
	cl_float			kr;
	cl_float			kt;
	cl_float			exp;
	cl_float			ls;

	int					texture_id;

	cl_uchar			is_reflective;
	cl_uchar			is_transparent;
	cl_uchar			gap[10];
};

int		create_material(t_material	type);

#endif
