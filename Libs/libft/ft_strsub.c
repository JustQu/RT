/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 03:52:49 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 08:39:55 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *p;
	char *rp;

	if (!s)
		return (NULL);
	if (!(p = (char *)malloc(len + 1)))
		return (NULL);
	rp = p;
	while (len--)
		*p++ = *(s + start++);
	*p = '\0';
	return (rp);
}
