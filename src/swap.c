/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:32:22 by dmelessa          #+#    #+#             */
/*   Updated: 2020/04/25 11:35:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CL\cl.h"

void	swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void	swap_float2(cl_float2 *a, cl_float2 *b)
{
	cl_float2 tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
