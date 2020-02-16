/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:27:44 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/17 15:50:19 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char *p;
	char *rp;

	if (!(p = ft_strnew(n + 1)))
		return (NULL);
	rp = p;
	while ((*p = *s1) && (size_t)(p - rp) < n)
	{
		p++;
		s1++;
	}
	ft_memset(p, 0, 1 + n - (p - rp));
	return (rp);
}
