/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:10:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 16:22:54 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_error.h"
#include "ocl_err_handl.h"

const char			*get_error_string_03(cl_int error)
{
	if (error == -34)
		return ("CL_INVALID_CONTEXT");
	if (error == -35)
		return ("CL_INVALID_QUEUE_PROPERTIES");
	if (error == -36)
		return ("CL_INVALID_COMMAND_QUEUE");
	if (error == -37)
		return ("CL_INVALID_HOST_PTR");
	if (error == -38)
		return ("CL_INVALID_MEM_OBJECT");
	if (error == -39)
		return ("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
	if (error == -40)
		return ("CL_INVALID_IMAGE_SIZE");
	if (error == -41)
		return ("CL_INVALID_SAMPLER");
	if (error == -42)
		return ("CL_INVALID_BINARY");
	if (error == -43)
		return ("CL_INVALID_BUILD_OPTIONS");
	if (error == -44)
		return ("CL_INVALID_PROGRAM");
	if (error == -45)
		return ("CL_INVALID_PROGRAM_EXECUTABLE");
	return (get_error_string_04(error));
}

const char			*get_error_string_02(cl_int error)
{
	if (error == -34)
		return ("CL_INVALID_CONTEXT");
	if (error == -35)
		return ("CL_INVALID_QUEUE_PROPERTIES");
	if (error == -36)
		return ("CL_INVALID_COMMAND_QUEUE");
	if (error == -37)
		return ("CL_INVALID_HOST_PTR");
	if (error == -38)
		return ("CL_INVALID_MEM_OBJECT");
	if (error == -39)
		return ("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");
	if (error == -40)
		return ("CL_INVALID_IMAGE_SIZE");
	if (error == -41)
		return ("CL_INVALID_SAMPLER");
	if (error == -42)
		return ("CL_INVALID_BINARY");
	if (error == -43)
		return ("CL_INVALID_BUILD_OPTIONS");
	if (error == -44)
		return ("CL_INVALID_PROGRAM");
	if (error == -45)
		return ("CL_INVALID_PROGRAM_EXECUTABLE");
	return (get_error_string_03(error));
}

const char			*get_error_string_01(cl_int error)
{
	if (error == -12)
		return ("CL_MAP_FAILURE");
	if (error == -13)
		return ("CL_MISALIGNED_SUB_BUFFER_OFFSET");
	if (error == -14)
		return ("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
	if (error == -15)
		return ("CL_COMPILE_PROGRAM_FAILURE");
	if (error == -16)
		return ("CL_LINKER_NOT_AVAILABLE");
	if (error == -17)
		return ("CL_LINK_PROGRAM_FAILURE");
	if (error == -18)
		return ("CL_DEVICE_PARTITION_FAILED");
	if (error == -19)
		return ("CL_KERNEL_ARG_INFO_NOT_AVAILABLE");
	if (error == -30)
		return ("CL_INVALID_VALUE");
	if (error == -31)
		return ("CL_INVALID_DEVICE_TYPE");
	if (error == -32)
		return ("CL_INVALID_PLATFORM");
	if (error == -33)
		return ("CL_INVALID_DEVICE");
	return (get_error_string_02(error));
}

const char			*get_error_string(cl_int error)
{
	if (error == 0)
		return ("CL_SUCCESS");
	if (error == -1)
		return ("CL_DEVICE_NOT_FOUND");
	if (error == -2)
		return ("CL_DEVICE_NOT_AVAILABLE");
	if (error == -3)
		return ("CL_COMPILER_NOT_AVAILABLE");
	if (error == -4)
		return ("CL_MEM_OBJECT_ALLOCATION_FAILURE");
	if (error == -5)
		return ("CL_OUT_OF_RESOURCES");
	if (error == -6)
		return ("CL_OUT_OF_HOST_MEMORY");
	if (error == -7)
		return ("CL_PROFILING_INFO_NOT_AVAILABLE");
	if (error == -8)
		return ("CL_MEM_COPY_OVERLAP");
	if (error == -9)
		return ("CL_IMAGE_FORMAT_MISMATCH");
	if (error == -10)
		return ("CL_IMAGE_FORMAT_NOT_SUPPORTED");
	if (error == -11)
		return ("CL_BUILD_PROGRAM_FAILURE");
	return (get_error_string_01(error));
}

/*
** @brief
** print log about opencl build fail
** @param program
** @param clp
** @param code
** @return ** void
*/

void				cl_error(t_cl_program *program, t_clp *clp, int code)
{
	char			*log;
	size_t			log_size;

	if (code != CL_SUCCESS)
	{
		ft_putnbr_fd(code, 2);
		ft_putstr_fd(": ", 2);
		clGetProgramBuildInfo(program->program, clp->de_id,
							CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = (char *)ft_memalloc(log_size);
		rt_is_dead(system_err, system_malloc_error, !log, "");
		clGetProgramBuildInfo(program->program, clp->de_id,
							CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putstr_fd(log, 2);
		ft_memdel((void **)&log);
	}
}
