/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 03:45:17 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 03:49:33 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*(s + i))
	{
		*(p + i) = f(i, *(s + i));
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
