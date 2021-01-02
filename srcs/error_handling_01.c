/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:00:27 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/20 15:16:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ocl_err_handl.h"

static const char		*get_error_string_06(cl_int error)
{
	if (error == -1001)
		return ("CL_PLATFORM_NOT_FOUND_KHR");
	if (error == -1002)
		return ("CL_INVALID_D3D10_DEVICE_KHR");
	if (error == -1003)
		return ("CL_INVALID_D3D10_RESOURCE_KHR");
	if (error == -1004)
		return ("CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR");
	if (error == -1005)
		return ("CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR");
	return ("Unknown OpenCL error");
}

static const char		*get_error_string_05(cl_int error)
{
	if (error == -58)
		return ("CL_INVALID_EVENT");
	if (error == -59)
		return ("CL_INVALID_OPERATION");
	if (error == -60)
		return ("CL_INVALID_GL_OBJECT");
	if (error == -61)
		return ("CL_INVALID_BUFFER_SIZE");
	if (error == -62)
		return ("CL_INVALID_MIP_LEVEL");
	if (error == -63)
		return ("CL_INVALID_GLOBAL_WORK_SIZE");
	if (error == -64)
		return ("CL_INVALID_PROPERTY");
	if (error == -65)
		return ("CL_INVALID_IMAGE_DESCRIPTOR");
	if (error == -66)
		return ("CL_INVALID_COMPILER_OPTIONS");
	if (error == -67)
		return ("CL_INVALID_LINKER_OPTIONS");
	if (error == -68)
		return ("CL_INVALID_DEVICE_PARTITION_COUNT");
	if (error == -1000)
		return ("CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR");
	return (get_error_string_06(error));
}

const char				*get_error_string_04(cl_int error)
{
	if (error == -46)
		return ("CL_INVALID_KERNEL_NAME");
	if (error == -47)
		return ("CL_INVALID_KERNEL_DEFINITION");
	if (error == -48)
		return ("CL_INVALID_KERNEL");
	if (error == -49)
		return ("CL_INVALID_ARG_INDEX");
	if (error == -50)
		return ("CL_INVALID_ARG_VALUE");
	if (error == -51)
		return ("CL_INVALID_ARG_SIZE");
	if (error == -52)
		return ("CL_INVALID_KERNEL_ARGS");
	if (error == -53)
		return ("CL_INVALID_WORK_DIMENSION");
	if (error == -54)
		return ("CL_INVALID_WORK_GROUP_SIZE");
	if (error == -55)
		return ("CL_INVALID_WORK_ITEM_SIZE");
	if (error == -56)
		return ("CL_INVALID_GLOBAL_OFFSET");
	if (error == -57)
		return ("CL_INVALID_EVENT_WAIT_LIST");
	return (get_error_string_05(error));
}
