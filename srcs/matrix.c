/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:23:02 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/13 12:37:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

/*
** @brief Multiplication of two matrices
**
** @param A
** @param B
** @return ** t_matrix
*/

t_matrix	mul_matrix(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			i;

	i = 0;
	while (i < 16)
	{
		c.s[i] = a.s[i / 4 * 4] * b.s[i % 4]
				+ a.s[i / 4 * 4 + 1] * b.s[i % 4 + 4]
				+ a.s[i / 4 * 4 + 2] * b.s[i % 4 + 8]
				+ a.s[i / 4 * 4 + 3] * b.s[i % 4 + 12];
		++i;
	}
	return (c);
}
