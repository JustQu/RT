/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:54:03 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:06:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

static void inline	set_kernel_args_01(t_rt rt, cl_kernel k, int err)
{
	static uint32_t	a;

	err |= clSetKernelArg(k, 12, sizeof(t_camera), &rt.scene.camera);
	err |= clSetKernelArg(k, 13, sizeof(t_light), &rt.scene.ambient_light);
	err |= clSetKernelArg(k, 14, sizeof(t_ambient_occluder),
						&rt.scene.ambient_occluder);
	err |= clSetKernelArg(k, 15, sizeof(cl_mem), &rt.ocl_program.bvh);
	err |= clSetKernelArg(k, 16, sizeof(t_rt_options), &rt.options);
	err |= clSetKernelArg(k, 17, sizeof(cl_mem), &rt.ocl_program.samplers);
	err |= clSetKernelArg(k, 18, sizeof(cl_mem), &rt.ocl_program.samples);
	err |= clSetKernelArg(k, 19, sizeof(cl_mem), &rt.ocl_program.disk_samples);
	err |= clSetKernelArg(k, 20, sizeof(cl_mem),
						&rt.ocl_program.hemisphere_samples);
	err |= clSetKernelArg(k, 21, sizeof(uint32_t), &a);
	err |= clSetKernelArg(k, 22, sizeof(cl_mem), &rt.ocl_program.textures);
	err |= clSetKernelArg(k, 23, sizeof(cl_mem), &rt.ocl_program.ranvec);
	err |= clSetKernelArg(k, 24, sizeof(cl_mem), &rt.ocl_program.perm_x);
	err |= clSetKernelArg(k, 25, sizeof(cl_mem), &rt.ocl_program.perm_y);
	err |= clSetKernelArg(k, 26, sizeof(cl_mem), &rt.ocl_program.perm_z);
	a++;
}

static void			set_kernel_args(t_rt rt, int step)
{
	cl_kernel		k;
	int				err;

	k = rt.ocl_program.new_kernel;
	err = 0;
	err |= clSetKernelArg(k, 0, sizeof(cl_mem), &rt.ocl_program.rgb_image);
	err |= clSetKernelArg(k, 1, sizeof(cl_int), &step);
	err |= clSetKernelArg(k, 2, sizeof(cl_mem), &rt.ocl_program.instances);
	err |= clSetKernelArg(k, 3, sizeof(cl_int),
							&rt.scene.instance_mngr.ninstances);
	err |= clSetKernelArg(k, 4, sizeof(cl_mem), &rt.ocl_program.objects);
	err |= clSetKernelArg(k, 5, sizeof(cl_int),
							&rt.scene.instance_mngr.nobjects);
	err |= clSetKernelArg(k, 6, sizeof(cl_mem), &rt.ocl_program.triangles);
	err |= clSetKernelArg(k, 7, sizeof(cl_int),
							&rt.scene.instance_mngr.ntriangles);
	err |= clSetKernelArg(k, 8, sizeof(cl_mem), &rt.ocl_program.matrices);
	err |= clSetKernelArg(k, 9, sizeof(cl_int),
							&rt.scene.instance_mngr.nmatrices);
	err |= clSetKernelArg(k, 10, sizeof(cl_mem), &rt.ocl_program.lights);
	err |= clSetKernelArg(k, 11, sizeof(cl_int),
							&rt.scene.light_manager.nlights);
	set_kernel_args_01(rt, k, err);
	rt_is_dead(opencl_err, cl_kernel_arg_error, err, "");
}

void				render_scene(t_rt rt)
{
	int				err;
	int				i;

	i = 0;
	while (i < NUM_SAMPLES)
	{
		set_kernel_args(rt, i);
		err = clEnqueueNDRangeKernel(rt.ocl_program.info.queue,
									rt.ocl_program.new_kernel,
									1, NULL,
									&rt.ocl_program.work_size,
									NULL,
									0, NULL, NULL);
		rt_is_dead(opencl_err, cl_kernel_start_error, err, "");
		i++;
	}
}

int					init_rt(t_app *app)
{
	init_sampler_manager(&app->rt.sampler_manager);
	init_default_options(app->resource_manager.rt_options,
					&app->rt.sampler_manager);
	if (init_parsed_scene(&app->rt.scene, &app->rt.sampler_manager,
					&app->resource_manager, app->options.scene_file) < 0)
		exit(-1000);
	rt_is_dead(app_err, app_no_objects,
				!app->rt.scene.instance_mngr.ninstances, "");
	rt_is_dead(app_err, app_no_lights,
				!app->rt.scene.light_manager.nlights, "");
	app->rt.scene.bvh = build_bvh(&app->rt.scene);
	init_ocl(&app->rt.ocl_program, &app->window, &app->image,
				app->options.render_device);
	init_buffers(&app->rt.ocl_program, &app->rt.scene,
			&app->rt.sampler_manager);
	return (SUCCESS);
}
