/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 04:14:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/14 16:46:34 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*p;
	const char	*sp;
	const char	*ep;

	if (!s)
		return (NULL);
	while (ft_isspace(*s))
		s++;
	sp = s;
	ep = sp;
	while (*sp)
	{
		while (*sp && !ft_isspace(*sp))
			sp++;
		ep = sp;
		while (*sp && ft_isspace(*sp))
			sp++;
	}
	sp = s;
	if (!(p = ft_strnew(ep - s)))
		return (NULL);
	ft_strncpy(p, s, ep - s);
	return (p);
}
