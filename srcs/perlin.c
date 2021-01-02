/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 00:31:48 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/21 17:28:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_types.h"
#include "utils.h"
#include "perlin.h"
#include "vector.h"
#include "rt_error.h"

#include <stdlib.h>
#include <math.h>

cl_float4	*perlin_generate(void)
{
	int			i;
	cl_float4	*p;

	p = ft_memalloc(sizeof(*p) * PERLIN_SIZE);
	if (!p)
		return (NULL);
	i = 0;
	while (i < PERLIN_SIZE)
	{
		p[i].w = rand_float();
		p[i].x = -1 + 2 * rand_float();
		p[i].y = -1 + 2 * rand_float();
		p[i].z = -1 + 2 * rand_float();
		i++;
	}
	return (p);
}

void		permute(int *p, int n)
{
	int	i;
	int	target;
	int	tmp;

	i = n - 1;
	while (i > 0)
	{
		target = (int)(rand_float() * (i + 1));
		tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
		i--;
	}
}

int			*perlin_generate_perm(void)
{
	int	*p;
	int	i;

	p = ft_memalloc(sizeof(int) * PERLIN_SIZE);
	rt_is_dead(system_err, system_malloc_error, !p, "");
	i = 0;
	while (i < PERLIN_SIZE)
	{
		p[i] = i;
		i++;
	}
	permute(p, PERLIN_SIZE);
	return (p);
}
