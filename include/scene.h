/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 00:33:50 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/22 00:28:49 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "light_manager.h"
# include "camera.h"
# include "bvh.h"
# include "instance_manager.h"
# include "sampler_manager.h"

typedef struct s_resource_manager	t_res_mngr;

/*
** @brief
** struct containing information about scene: camera, objects,
** triangles and light sources
*/

typedef struct s_scene				t_scene;
struct								s_scene
{
	t_camera						camera;
	t_instance_manager				instance_mngr;
	t_ambient_occluder				ambient_occluder;
	t_light_manager					light_manager;
	t_light							ambient_light;
	t_bvh							bvh;
	uint32_t						gap[2];
};

int									init_default_scene(t_scene *scene,
											t_sampler_manager *sampler_manager,
											t_res_mngr *resource_manager);
int									init_parsed_scene(t_scene *scene,
											t_sampler_manager *sampler_manager,
											t_res_mngr *resource_manager,
											char *scene_file);
t_bvh								build_bvh(t_scene *scene);
int									parser(t_res_mngr *resource_manager,
											t_parsed_info *asset,
											char *file_name);
void								pars_camera(char *str,
												t_camera *camera, int log);
void								pars_light(char *str,
												t_parsed_info *asset,
												t_res_mngr *res_mngr, int log);
void								pars_object(t_res_mngr *resource_manager,
												t_parsed_info *asset,
												char *str, int log);
void								pars_options(char *str, t_res_mngr *mngr);

#endif
