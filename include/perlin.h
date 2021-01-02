/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 13:19:10 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/03 21:57:59 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H

# include "rt_types.h"

# define PERLIN_SIZE 256

cl_float3	*perlin_generate();
void		permute(int *p, int n);
int			*perlin_generate_perm();

#endif
