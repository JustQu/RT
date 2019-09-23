/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:29:51 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:30:32 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
# define VEC4_H

# include "rt_types.h"

# define VEC4_ONE_INIT   {1.0f, 1.0f, 1.0f, 1.0f}
# define VEC4_ZERO_INIT  {0.0f, 0.0f, 0.0f, 0.0f}
# define VEC4_ONE        ((t_vec4)VEC4_ONE_INIT)
# define VEC4_ZERO       ((t_vec4)VEC4_ZERO_INIT)

void	vec3_to_vec4(t_vec3 v3, float last, t_vec4 dest);
void	vec4_copy(t_vec4 v, t_vec4 dest);
void	vec4_zero(t_vec4 v);
void	vec4_one(t_vec4 v);
float	vec4_dot(t_vec4 a, t_vec4 b);
float	vec4_norm2(t_vec4 v);
float	vec4_norm(t_vec4 v);
void	vec4_sum(t_vec4 a, t_vec4 b, t_vec4 dest);
void	vec4_adds(t_vec4 v, float s, t_vec4 dest);
void	vec4_sub(t_vec4 a, t_vec4 b, t_vec4 dest);
void	vec4_subs(t_vec4 v, float s, t_vec4 dest);
void	vec4_mul(t_vec4 a, t_vec4 b, t_vec4 dest);
void	vec4_scale(t_vec4 a, float s, t_vec4 dest);
void	vec4_scale_as(t_vec4 v, float s, t_vec4 dest);
void	vec4_negate_to(t_vec4 v, t_vec4 dest);
void	vec4_negate(t_vec4 v);
void	vec4_normalize_to(t_vec4 v, t_vec4 dest);
void	vec4_normalize(t_vec4 v);
float	vec4_distance(t_vec4 a, t_vec4 b);
void	vec4_broadcast(float val, t_vec4 d);
void	vec4_lerp(t_vec4 from, t_vec4 to, float t, t_vec4 dest);
void	vec4_muladds(t_vec4 a, float s, t_vec4 dest);

#endif
