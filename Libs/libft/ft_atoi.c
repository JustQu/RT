/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 02:58:41 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/19 16:13:31 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	sign;

	a = 0;
	sign = 0;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = *str++ == '-' ? 1 : 0;
	while (ft_isdigit(*str))
		a = a * 10 + (*str++ - '0');
	return (sign ? -a : a);
}
