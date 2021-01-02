/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:34:20 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/04 20:34:49 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

float	rand_float(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

int		rand_int(void)
{
	return (rand());
}
