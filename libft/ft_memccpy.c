/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:49:30 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/17 17:58:50 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if ((*((unsigned char *)dst + i) = *((unsigned char *)src + i))
				== (unsigned char)c)
			return ((unsigned char *)dst + i + 1);
		i++;
	}
	return (NULL);
}
