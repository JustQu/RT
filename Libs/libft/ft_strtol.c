/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:43:53 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/05 15:43:29 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_strtol(const char *s, char **endptr, int b)
{
	int	neg;
	int acc;

	neg = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		neg = (*s++ == '-' ? -1 : 1);
	if ((b == 0 || b == 16) && *s == '0' && (s[1] == 'x' || *(s + 1) == 'X'))
		b = (s += 2) ? 16 : 16;
	if (b == 0)
		b = *s == '0' ? 8 : 10;
	acc = 0;
	while (*s && ft_isbase(*s, b))
	{
		if (ft_isalpha(*s) && (*s - (ft_isupper(*s) ? 'A' - 10 : 'a' - 10) < b))
			acc = acc * b - (ft_isupper(*s) ? 'A' - 10 : 'a' - 10) + *s;
		else if (ft_isdigit(*s) && (*s - '0') < b)
			acc = acc * b + (*s - '0');
		else
			break ;
		s++;
	}
	return ((*endptr = (char *)s) ? acc * (neg) : acc * (neg));
}
