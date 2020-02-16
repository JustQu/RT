/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 03:42:53 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 18:29:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *p;
	char *rp;

	if (!s || !f)
		return (NULL);
	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	rp = p;
	while (*s)
	{
		*p++ = f(*s);
		s++;
	}
	*p = '\0';
	return (rp);
}
