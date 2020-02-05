/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:22:50 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 01:24:34 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *p;
	char *rp;

	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	rp = p;
	while ((*rp++ = *s++))
		;
	return (p);
}
