/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 04:28:25 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/14 20:02:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	char	*p;
	int		size;
	int		tmp;

	size = 1;
	sign = n < 0 ? 1 : 0;
	tmp = n;
	while (tmp /= 10)
		size++;
	if (!(p = (char *)malloc(size + sign + 1)))
		return (NULL);
	*(p + size + sign) = '\0';
	if (sign)
		*p++ = '-';
	while (size--)
	{
		*(p + size) = (((n % 10) < 0) ? -(n % 10) : (n % 10)) + '0';
		n /= 10;
	}
	return (p - sign);
}
