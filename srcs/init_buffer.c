/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 23:27:18 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 17:13:47 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_error.h"

static void		init_buffers3(t_cl_program *p, t_scene *s)
{
	int			ret;
	int			ro;
	cl_context	cntx;

	ro = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	cntx = p->info.context;
	p->textures = clCreateBuffer(cntx, ro, sizeof(t_texture) *
							s->instance_mngr.texture_manager.ntextures,
							s->instance_mngr.texture_manager.textures, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->ranvec = clCreateBuffer(cntx, ro,
				sizeof(*s->instance_mngr.texture_manager.ranvec) * PERLIN_SIZE,
				s->instance_mngr.texture_manager.ranvec, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->perm_x = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
								s->instance_mngr.texture_manager.perm_x, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->perm_y = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
								s->instance_mngr.texture_manager.perm_y, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->perm_z = clCreateBuffer(cntx, ro, sizeof(cl_int) * PERLIN_SIZE,
								s->instance_mngr.texture_manager.perm_z, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
}

static void		init_buffers2(t_cl_program *p, t_scene *s,
						t_sampler_manager *sampler_manager)
{
	int			ret;
	int			ro;
	cl_context	cntx;

	ro = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	cntx = p->info.context;
	p->bvh = clCreateBuffer(cntx, ro, sizeof(t_bvh_node) *
							(s->instance_mngr.ninstances * 2), s->bvh, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->lights = clCreateBuffer(cntx, ro, sizeof(t_light) *
				(s->light_manager.nlights + 1), s->light_manager.lights, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->samplers = clCreateBuffer(cntx, ro, sizeof(t_sampler) *
					sampler_manager->count, sampler_manager->samplers, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->samples = clCreateBuffer(cntx, ro, sampler_manager->samples_size,
								sampler_manager->samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->disk_samples = clCreateBuffer(cntx, ro, sampler_manager->
						disk_samples_size, sampler_manager->disk_samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->hemisphere_samples = clCreateBuffer(cntx, ro, sampler_manager->
			hemisphere_samples_size, sampler_manager->hemisphere_samples, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	init_buffers3(p, s);
}

/*
** @brief
** @todo: deal with  case when there is no objects
** @param program
** @param scene
** @param sampler_manager
** @param rt
** @return ** void
*/

void			init_buffers(t_cl_program *const p,
							t_scene *const s,
							t_sampler_manager *const sampler_manager)
{
	int			ret;
	int			ro;
	cl_context	cntx;

	ro = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	cntx = p->info.context;
	p->rgb_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
								sizeof(t_color) * p->work_size, NULL, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->output_image = clCreateBuffer(cntx, CL_MEM_READ_WRITE,
								sizeof(uint32_t) * p->work_size, NULL, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->instances = clCreateBuffer(cntx, ro, sizeof(t_instance) *
				s->instance_mngr.ninstances, s->instance_mngr.instances, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->objects = clCreateBuffer(cntx, ro, sizeof(t_obj) *
					s->instance_mngr.nobjects + 1, s->instance_mngr.objects, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->triangles = clCreateBuffer(cntx, ro, sizeof(t_triangle) * (s->
			instance_mngr.ntriangles + 1), s->instance_mngr.triangles, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	p->matrices = clCreateBuffer(cntx, ro, sizeof(t_matrix) *
				s->instance_mngr.nmatrices, s->instance_mngr.matrices, &ret);
	rt_is_dead(opencl_err, cl_create_buffer_error, ret, "");
	init_buffers2(p, s, sampler_manager);
}
