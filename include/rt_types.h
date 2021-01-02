/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:57:17 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 15:22:29 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# ifndef __OPENCL_C_VERSION__
#  include "inttypes.h"
#  include "float.h"
#  include "bool.h"
#  ifdef __APPLE__
#   include "OpenCL/opencl.h"
#  else
#   include "CL/cl.h"
#  endif

typedef uint32_t	t_uint;
typedef int32_t		t_int;
typedef int8_t		t_s8;
typedef int16_t		t_s16;
typedef int32_t		t_s32;
typedef int64_t		t_s64;

typedef uint8_t		t_u8;
typedef uint16_t	t_u16;
typedef uint32_t	t_u32;
typedef uint64_t	t_u64;

typedef cl_float	t_float;
typedef cl_float2	t_float2;
typedef cl_float4	t_float4;
typedef cl_float8	t_float8;
typedef cl_float16	t_float16;

# endif

# define SUCCESS	0
# define ERROR	-1

# define DEG2RAD (float)M_PI / 360.0f

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
# endif

#endif
