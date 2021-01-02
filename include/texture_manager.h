/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 14:41:15 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 22:17:52 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_H
# define TEXTURE_MANAGER_H

# include "rt_types.h"
# include "texture.h"
# include "perlin.h"

typedef struct s_texture_manager	t_texture_manager;

struct		s_texture_manager
{
	t_texture	*textures;
	char		*imgs_data;
	cl_float4	*ranvec;
	int			*perm_x;
	int			*perm_y;
	int			*perm_z;
	size_t		textures_malloc_size;
	size_t		imgs_data_malloc_size;
	int			nimgs;
	int			ntextures;
	int			current_offset;
};

int			init_texture_manager(t_texture_manager *texture_manager);
int			add_texture(t_texture_manager *texture_manager, t_texture texture);
int			new_texture(t_texture_manager *texture_manager,
					t_texture_type type);
t_texture	*get_texutre(t_texture_manager *texture_manager, int id);

void		set_type(t_texture_manager *texture_manager, int id);
void		get_type(t_texture_manager *texture_manager, int id);

void		set_color1(t_texture_manager *texture_manager, int id);
t_color		get_color1(t_texture_manager *texture_manager, int id);

void		set_color2(t_texture_manager *texture_manager, int id);
void		get_color2(t_texture_manager *texture_manager, int id);

#endif
