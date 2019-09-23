/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:58:53 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:57:53 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "rt_types.h"
# include "math.h"
# include "vec4.h"
# include "utils.h"

# define RTM_VEC3_ONE_INIT  {1.0f, 1.0f, 1.0f}
# define RTM_VEC3_ZERO_INIT {0.0f, 0.0f, 0.0f}
# define RTM_VEC3_ONE       ((t_vec3){1.0f, 1.0f, 1.0f})
# define RTM_VEC3_ZERO      ((t_vec3){0.0f, 0.0f, 0.0f})
# define RTM_YUP            ((t_vec3){0.0f, 1.0f, 0.0f})
# define RTM_ZUP            ((t_vec3){0.0f, 0.0f, 1.0f})
# define RTM_XUP            ((t_vec3){1.0f, 0.0f, 0.0f})

/*
**init vec3 using vec4
*/
void	vec4_to_vec3(t_vec4 v4, t_vec3 dest);

/*
**copy all members of [a] to [dest]
*/
void	vec3_copy(t_vec3 a, t_vec3 dest);

/*
**make vector zero
*/
void	vec3_zero(t_vec3 v);

/*
**make vector one
*/
void	vec3_one(t_vec3 v);

/*
**vec3 dot product
*/
float	vec3_dot(t_vec3 a, t_vec3 b);

/*
**norm * norm (magnitude) of vec
*/
float	vec3_norm2(t_vec3 v);

/*
**norm (magnitude of vec3)
*/
float	vec3_norm(t_vec3 v);

/*
**vec3 dot product
*/
float	vec3_dot(t_vec3 a, t_vec3 b);

/*
**add scalar to v vector store result in dest (d = v + s)
*/
void	vec3_adds(t_vec3 v, float s, t_vec3 dest);

/*
**substract scalar from v vector store result in dest (d = v - s)
*/
void	vec3_subs(t_vec3 v, float s, t_vec3 dest);

/*
**add a vector to b vector store result in dest
*/
void	vec3_sum(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
**substract b vector from a vector store result in dest
*/
void	vec3_sub(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
**multiply/scale vec4 vector with scalar: result = v * s
*/
void	vec3_scale(t_vec3 v, float s, t_vec3 dest);

/*
**multiply two vector (component-wise multiplication)
*/
void	vec3_mul(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
**negate vector components and store result in dest
*/
void	vec3_negate_to(t_vec3 v, t_vec3 dest);

/*
**negate vector components
*/
void	vec3_negate(t_vec3 v);

/*
**normalize vec3 and store result in same vec
*/
void	vec3_normalize(t_vec3 v);

/*
**normalize vec3 and store result in dest
*/
void	vec3_normalize_to(t_vec3 v, t_vec3 dest);

/*
**cross product of two vector
**(u2.v3 - u3.v2, u3.v1 - u1.v3, u1.v2 - u2.v1)
*/
void	vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
** angle between two vector
*/
float	vec3_angle(t_vec3 a, t_vec3 b);

/*
** rotate vec3 around axis by angle using Rodrigues' rotation formula
*/
void	vec3_rotate(t_vec3 v, float angle, t_vec3 axis);

/*
** apply rotation matrix to vector
*/
void	vec3_rotate_m4(t_mat4 m, t_vec3 v, t_vec3 dest);

/*
** apply rotation matrix to vector
*/
void	vec3_rotate_m3(t_mat3 m, t_vec3 v, t_vec3 dest);

/*
**project a vector onto b vector
*/
void	vec3_proj(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
**find center point of two vector
*/
void	vec3_center(t_vec3 a, t_vec3 b, t_vec3 dest);

/*
**squared distance between two vectors
*/
float	t_vec3_distance2(t_vec3 a, t_vec3 b);

/*
**distance beween two vector
*/
float	vec3_distance(t_vec3 a, t_vec3 b);

/*
**fill a vector with specified value
*/
void	vec3_broadcast(float val, t_vec3 d);

/*
**linear interpolation between two vector
**formula: from + s * (to - from)
**t	interpolant (amount) clamped between 0 and 1
*/
void	vec3_lerp(t_vec3 from, t_vec3 to, float t, t_vec3 dest);

/*
**vec3 cross product
**this is just convenient wrapper
*/
void	cross(t_vec3 a, t_vec3 b, t_vec3 d);

/*
**vec3 dot product
**this is just convenient wrapper
*/
float	dot(t_vec3 a, t_vec3 b);

/*
**normalize vec3 and store result in same vec
**this is just convenient wrapper
*/
void	normalize(t_vec3 v);

/*
**normalize vec3 to dest
**this is just convenient wrapper
*/
void	normalize_to(t_vec3 v, t_vec3 dest);

#endif
