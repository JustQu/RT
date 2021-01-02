/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 18:12:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/08 17:08:13 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTANCE_MANAGER_H
# define INSTANCE_MANAGER_H

# include "instance.h"
# include "objects.h"
# include "matrix.h"
# include "parser.h"
# include "texture_manager.h"

typedef struct			s_instance_info
{
	t_material			material;
	t_texture			texture;
	cl_float4			origin;
	cl_float4			v1;
	cl_float4			v2;
	cl_float4			v3;
	cl_float4			rotation;
	cl_float4			scaling;
	t_type				type;
	float				r;
	float				r2;
	float				e;
	float				height;
	int					boolean;
	int					gap[2];
}						t_instance_info;

typedef struct			s_instance_extra
{
	t_aabb				aabb;
	cl_float4			origin;
	cl_float4			rotation;
	cl_float4			scaling;
}						t_instance_extra;

typedef struct			s_instance_manager
{
	t_texture_manager	texture_manager;
	t_instance			*instances;
	t_obj				*objects;
	t_triangle			*triangles;
	t_matrix			*matrices;
	t_instance_extra	*extra;
	size_t				instances_malloc_size;
	size_t				objects_malloc_size;
	size_t				triangles_malloc_size;
	size_t				matrices_malloc_size;
	size_t				extra_size;
	int					ninstances;
	int					nobjects;
	int					ntriangles;
	int					nmatrices;
	uint32_t			gap[4];
}						t_instance_manager;

int						init_instance_manager(t_instance_manager
					*instance_manager);

int						add_object(t_instance_manager *instance_manager,
							t_instance_info object_info);
int						add_matrix(t_instance_manager *mngr,
							t_matrix matrix);

t_matrix				get_transformation_matrix(t_instance_info info);
t_matrix				create_inv_transformation_matrix(t_instance_info info);

t_aabb					compute_aabb(t_instance_info info);

void					set_sampler(t_instance_manager *instance_manager,
							int id, int sampler_id);

#endif
