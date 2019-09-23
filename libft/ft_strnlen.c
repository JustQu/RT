/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:17:19 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 01:22:24 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t slen;

	slen = 0;
	while (*(s + slen))
	{
		if (slen == maxlen)
			return (slen);
		slen++;
	}
	return (slen);
}
