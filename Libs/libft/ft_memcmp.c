/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:16:32 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 01:16:51 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char c1;
	unsigned char c2;

	c1 = '\0';
	c2 = '\0';
	while (n > 0)
	{
		c1 = *(unsigned char *)s1;
		c2 = *(unsigned char *)s2;
		s1 = (unsigned char *)s1 + 1;
		s2 = (unsigned char *)s2 + 1;
		if (c1 != c2)
			return (c1 - c2);
		n--;
	}
	return (c1 - c2);
}
