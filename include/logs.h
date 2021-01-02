/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:10:52 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/10 18:23:24 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGS_H
# define LOGS_H

# include "parser.h"
# include "resource_manager.h"

# define UNKNOWN_SCENE_TYPE					-1
# define SCENE_TYPE_DOES_NOT_EXIST			-2
# define OBJ_TYPE_DOES_NOT_EXIST			-3
# define MATERIAL_TYPE_DOES_NOT_EXIST		-4
# define TEXTURE_TYPE_DOES_NOT_EXIST		-5
# define WRITE_BLOCK						-6
# define COMMENT							-7
# define BAD_BRACKETS						-8
# define VALID_BLOCK						-9
# define UNKNOWN_OBJ_TYPE					-10
# define UNKNOWN_MATERIAL_TYPE				-11
# define UNKNOWN_TEXTURE_TYPE				-12
# define COLOR_DOES_NOT_EXIST				-13
# define PARS_SUCCESS						-14
# define PARS_UNSUCCESS						-15
# define BAD_ORIGIN							-16
# define BAD_ROTATION						-17
# define BAD_SOLID_COLOR					-18
# define BAD_EVEN_COLOR						-19
# define BAD_ODD_COLOR						-20
# define BAD_CAMERA_ORIGIN					-21
# define BAD_CAMERA_DIRECTION				-22
# define BAD_CAMERA_ZOOM					-23
# define BAD_CAMERA_TYPE					-24
# define NO_CAMERA							-25
# define ANGLE_DOES_NOT_EXIST				-27
# define BAD_MINM_MAXM						-28
# define RADIUS_DOES_NOT_EXIST				-29
# define VECTORS_DOES_NOT_EXIST				-30
# define BAD_DIFFUSE_COEFFICIEN				-31
# define BAD_INTENSITY						-32
# define BAD_REFLECTIVE						-33
# define BAD_ROUGHNESS						-34
# define BAD_TRANSMISSION					-35
# define BAD_SPECULAR						-36
# define BAD_AMBIENT						-37
# define BAD_LIGHT_TYPE						-38

void		write_logs(int num_log, int fd, char *str);
void		validate_cone(t_res_mngr *mngr, t_parsed_info asset, int log);
int			validate_default(t_parsed_info *asset, int log);
void		validate_cylinder(t_res_mngr *mngr, t_parsed_info asset, int log);
void		validate_paraboloid(t_res_mngr *mngr, t_parsed_info asset, int log);
void		validate_plane(t_res_mngr *mngr, t_parsed_info asset, int log);
void		validate_sphere(t_res_mngr *mngr, t_parsed_info asset, int log);
void		validate_torus_disk(t_res_mngr *mngr, t_parsed_info asset, int log);
void		validate_triangle_box(t_res_mngr *mngr,
							t_parsed_info asset, int log);
void		validate_rectangle(t_res_mngr *mngr, t_parsed_info asset, int log);
int			validate_texture(t_parsed_info *asset, int log);
int			validate_material(t_parsed_info *asset, int log);
void		write_logs_5(int num_log, int fd, char *str);
void		write_logs_10(int num_log, int fd, char *str);

#endif
