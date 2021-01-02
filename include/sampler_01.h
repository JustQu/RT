/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler_01.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 20:20:17 by jvoor             #+#    #+#             */
/*   Updated: 2020/12/15 20:22:14 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLER_01_H
# define SAMPLER_01_H

cl_float2		*generate_rand_jitter_samples(t_sampler sampler,
			cl_float2 *samples);
cl_float2		*generate_regular_samples(t_sampler sampler,
			cl_float2 *samples);
cl_float2		*generate_pure_random_samples(t_sampler sampler,
			cl_float2 *samples);
void			shuffle_x_coordinates(cl_float2 *samples,
			t_sampler sampler);
void			shuffle_y_coordinates(cl_float2 *samples,
			t_sampler sampler);

#endif
