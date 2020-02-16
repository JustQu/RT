/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:10:45 by dmelessa          #+#    #+#             */
/*   Updated: 2020/02/16 18:56:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/**
** @brief
** print log about opencl build fail
** @param program
** @param clp
** @param code
** @return ** void
*/
void cl_error(t_cl_program *program, t_clp *clp, int code)
{
	if (code != CL_SUCCESS)
	{
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG, 0,
							  NULL, &log_size);
		// Allocate memory for the log
		char *log = (char *)malloc(log_size);
		// Get the log
		clGetProgramBuildInfo(program->program, clp->de_id, CL_PROGRAM_BUILD_LOG,
							  log_size, log, NULL);
		// Print the log
		printf("%d: %s\n", code, log);
		assert(!code);
	}
}
