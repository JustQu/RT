/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_buffers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 16:04:56 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 16:08:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "rt_ocl.h"

void		cleanup_buffers(t_cl_program ocl_program)
{
	clReleaseMemObject(ocl_program.instances);
	clReleaseMemObject(ocl_program.objects);
	clReleaseMemObject(ocl_program.triangles);
	clReleaseMemObject(ocl_program.lights);
	clReleaseMemObject(ocl_program.bvh);
	clReleaseMemObject(ocl_program.matrices);
	clReleaseMemObject(ocl_program.samplers);
	clReleaseMemObject(ocl_program.samples);
	clReleaseMemObject(ocl_program.disk_samples);
	clReleaseMemObject(ocl_program.hemisphere_samples);
	clReleaseMemObject(ocl_program.textures);
	clReleaseMemObject(ocl_program.perm_x);
	clReleaseMemObject(ocl_program.perm_y);
	clReleaseMemObject(ocl_program.perm_z);
	clReleaseMemObject(ocl_program.ranvec);
}

static void	cleanup2(t_app app)
{
	cleanup_buffers(app.rt.ocl_program);
	SDL_DestroyTexture(app.window.texture);
	SDL_DestroyRenderer(app.window.renderer);
	SDL_DestroyWindow(app.window.ptr);
	clReleaseKernel(app.rt.ocl_program.help_kernel);
	clReleaseKernel(app.rt.ocl_program.new_kernel);
	clReleaseCommandQueue(app.rt.ocl_program.info.queue);
	clReleaseContext(app.rt.ocl_program.info.context);
	clReleaseMemObject(app.rt.ocl_program.rgb_image);
	clReleaseMemObject(app.rt.ocl_program.output_image);
}

/*
** @brief free all alocated memory and objects
**
** @param app
** @return ** void
*/

void		cleanup(t_app app)
{
	ft_memdel((void **)&app.image.pixels);
	ft_memdel((void **)&app.image.rgb);
	ft_memdel((void **)&app.rt.sampler_manager.samplers);
	ft_memdel((void **)&app.rt.sampler_manager.samples);
	ft_memdel((void **)&app.rt.sampler_manager.disk_samples);
	ft_memdel((void **)&app.rt.sampler_manager.hemisphere_samples);
	ft_memdel((void **)&app.rt.scene.instance_mngr.instances);
	ft_memdel((void **)&app.rt.scene.instance_mngr.extra);
	ft_memdel((void **)&app.rt.scene.instance_mngr.objects);
	ft_memdel((void **)&app.rt.scene.instance_mngr.matrices);
	ft_memdel((void **)&app.rt.scene.instance_mngr.triangles);
	ft_memdel((void **)&app.rt.scene.light_manager.lights);
	ft_memdel((void **)&app.rt.scene.bvh);
	ft_memdel((void **)&app.rt.scene.instance_mngr.texture_manager.textures);
	ft_memdel((void **)&app.rt.scene.instance_mngr.texture_manager.ranvec);
	ft_memdel((void **)&app.rt.scene.instance_mngr.texture_manager.perm_x);
	ft_memdel((void **)&app.rt.scene.instance_mngr.texture_manager.perm_y);
	ft_memdel((void **)&app.rt.scene.instance_mngr.texture_manager.perm_z);
	cleanup2(app);
}
