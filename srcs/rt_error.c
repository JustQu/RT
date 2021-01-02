/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:02:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:07:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"

void	rt_warning(const char *message)
{
	ft_putendl(message);
}

static t_code_msg	g_code_msg[] = {
	{system_err, system_malloc_error, "Error! Could not allocate memory."},
	{sdl_err, sdl_create_window_error, "Error! Could not create SDL window." },

	{opencl_err, cl_get_platform_id_error, "Error! Could not get platform id."},
	{opencl_err, cl_get_device_id_error, "Error! Could not get device id."},
	{opencl_err, cl_create_context_error,
		"Error! Could not create OpenCL_err context."},
	{opencl_err, cl_create_command_queue_error,
		"Error! Could not create command queue."},
	{opencl_err, cl_kernel_arg_error,
		"Error! Could not pass argument to kernel."},
	{opencl_err, cl_kernel_start_error, "Error! Could not start kernel."},
	{opencl_err, cl_read_buffer_error, "Error! Could not read from buffer."},
	{opencl_err, cl_create_program_error, "Error! Could not create program."},
	{opencl_err, cl_build_program_error,
		"Error! Could not build OpenCL program"},
	{opencl_err, cl_create_kernel_error,
		"Error! Could not create OpenCL kernel"},
	{opencl_err, cl_create_buffer_error,
		"Error! Could not create buffer for OpenCL."},

	{app_err, app_no_scene_file, "Error! Could not open scene file."},
	{app_err, app_unknown_object_type, "Error! Unknow object type."},

	{app_err, app_no_objects, "Error! No objecs in the scene file."},
	{app_err, app_no_lights, "Error! No lights in the scene file."},
	{app_err, undefinded_error, "Something went wrong!"},
};
static t_u32		g_nmsgs = sizeof(g_code_msg) / sizeof(t_code_msg);

/*
** @brief print error message and exit program.
** we are letting OS free all the memory in case of error
**
** @param err_code
** @param additional_message
** @return ** void
*/

void	rt_is_dead(t_error_type err_type, t_error_code err_code,
					t_s32 c,
					const char *additional_message)
{
	t_u32	i;

	if (err_code == 0 || c == 0)
		return ;
	i = 0;
	if (err_code < 0)
		while (err_code != g_code_msg[i].err_code && i < g_nmsgs)
			i++;
	ft_putendl_fd(g_code_msg[i].msg, 2);
	if (err_type == opencl_err)
		ft_putendl_fd(get_error_string(c), 2);
	else if (err_type == sdl_err)
		ft_putendl_fd(SDL_GetError(), 2);
	else if (err_type == system_err)
		perror("");
	ft_putendl_fd(additional_message, 2);
	exit(g_code_msg[i].err_code);
}
