/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 06:46:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 06:50:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char *pneedle = needle;

	if (!*needle)
		return ((char *)haystack);
	while (len-- && *haystack && *needle)
		if (*haystack++ == *needle)
			needle++;
		else
		{
			haystack -= needle - pneedle;
			len += needle - pneedle;
			needle = pneedle;
		}
	return (*needle ? NULL : (char *)(haystack - (needle - pneedle)));
}
