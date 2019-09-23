/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:51:02 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 01:54:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *p;
	const char *rp;

	if (c == '\0')
		return (ft_strchr(s, '\0'));
	rp = NULL;
	while ((p = ft_strchr(s, c)) != NULL)
	{
		rp = p;
		s = p + 1;
	}
	return ((char *)rp);
}
