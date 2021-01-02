/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:54:56 by rmaxima           #+#    #+#             */
/*   Updated: 2020/12/20 20:16:44 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)dst;
	str2 = (unsigned char*)src;
	if (str1 == str2)
		return (dst);
	if (str2 < str1)
	{
		str2 = (unsigned char *)src + len - 1;
		str1 = (unsigned char *)dst + len - 1;
		while (len--)
			*str1-- = *str2--;
	}
	else
	{
		while (len--)
			*str1++ = *str2++;
	}
	return (dst);
}
