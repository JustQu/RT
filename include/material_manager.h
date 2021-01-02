/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_manager.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 00:35:05 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:43:15 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_MANAGER_H
# define MATERIAL_MANAGER_H

# include "material.h"

typedef struct s_material_manager	t_material_manager;

struct		s_material_manager
{
	int		todo;
};

int			init_material_manager(t_material_manager *material_manager);
int			new_material(t_material_manager *material_manager);
int			add_material(t_material_manager *material_manager,
						t_material material);

t_material	*get_material(t_material_manager *material_manager, int id);

#endif
