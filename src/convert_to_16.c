/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:08:20 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	convert_to16(int val, char *num, char *ax)
{
	char	*tmp;
	char	swap;

	if (!val)
		return ;
	tmp = num;
	while (val > 0)
	{
		*num = ax[val % 16];
		num++;
		val = val / 16;
	}
	num--;
	while (num - tmp > 0)
	{
		swap = *tmp;
		*tmp = *num;
		*num = swap;
		num--;
		tmp++;
	}
}
