/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:05:29 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/22 00:23:36 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "material.h"
# include "objects.h"
# include "light.h"
# include "texture.h"
# include "libft.h"
# include "camera.h"
# include <math.h>

typedef enum e_block_type	t_block_type;

typedef enum				e_ambient_illumination
{
	no,
	constant,
	occluder,
}							t_ambient_illumination;

typedef enum				e_parsed_type
{
	object,
	light,
	camera,
	options,
}							t_parsed_type;

typedef struct				s_parsed_object
{
	t_material				material;
	t_texture				texture;
	cl_float4				origin;
	cl_float4				vector1;
	cl_float4				vector2;
	cl_float4				direction;
	cl_float3				rotation;
	cl_float3				scaling;
	cl_float				minm;
	cl_float				maxm;
	cl_float				r;
	cl_float				r2;
	t_type					type;
	cl_int					boolean;
}							t_parsed_object;

typedef struct				s_parsed_light
{
	cl_float4				origin;
	cl_float4				direction;
	t_color					color;
	cl_float				ls;
	t_light_type			type;
	cl_float				pdf;
}							t_parsed_light;

typedef union				u_parsed_data
{
	t_parsed_object			object;
	t_parsed_light			light;
}							t_parsed_data;

typedef struct				s_parsed_info
{
	t_parsed_type			type;
	t_parsed_data			data;
}							t_parsed_info;

int							str_len(char *str);
char						*get_key(char **str);
char						*get_value(char **str);
t_parsed_object				get_default_obj();
t_parsed_light				get_default_light();
t_camera					get_default_camera();
void						get_default_material(t_material *material);
void						get_default_texture(t_texture *texture);
int							get_log_fd(char *str);
void						get_ambient_illumination(char *str, int offset,
													void *data);
int							check_brackets(char *str);
int							get_block_type(char *str);
int							block_type_lengh(char *str);
int							check_block_type(char *str);
void						to_lower(char *str);
int							char_count(char *str);
void						free_tab(char **tab);
int							len_word(char *str);
char						*basename(const char *filename);

#endif
