/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 17:53:59 by dmelessa          #+#    #+#             */
/*   Updated: 2020/05/16 18:04:10 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLER_H
# define SAMPLER_H

#include "types.h"

typedef enum e_sampler_type			t_sampler_type;
typedef struct s_sampler			t_sampler;

enum	e_sampler_type
{
		none, //maybe we can replace it with regular grid where is onlu one sample per pixel
		regular_grid,
		jitter,
		rand_jitter,
		pure_random,
		nrooks
};

/*
** Sample types flags
*/
#define DEFAULT_SAMPLES		1 << 0
#define DISK_SAMPLES		1 << 1
#define HEMISPHERE_SAMPLES	1 << 2

# ifdef _WIN64
__declspec(align(4))
# endif
struct				s_sampler
{
	t_sampler_type	type;
	cl_int			num_samples; /* the number of sample points in a pattern */
	cl_int			num_sets;	/* the number of sample sets(patterns) stores */
	cl_uint			count;		/* the currenct numer of sample points used */
	cl_int			jump;		// random index jump
	cl_int			samples_type; // default / disk / hemisphere
	// cl_int			shuffled_indices[NUM_SAMPLES * NUM_SETS];

	cl_int			offset;
	// cl_int			disk_samples_offset;
	// cl_int			hemisphere_samples_offset;
};


#endif
