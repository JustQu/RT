/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 00:07:37 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/16 20:18:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "types.h"
# include "color.h"

typedef enum e_material_type		t_material_type;
typedef struct s_material			t_material;
enum e_material_type
{
	matte, //kd, ka
	phong,
	emissive
};

# ifdef _WIN64
__declspec(align(4))
# endif
struct					s_material //kd + ks < 1.0
{
	t_material_type		type;
	t_color				color;
	cl_float			kd; //diffuse reflection coefficient [0, 1]
	cl_float			ka; //ambient reflection
	cl_float			ks; //coefficient of specular reflection [0, 1]
	cl_float			exp;
	void				*texture;
};

#endif
