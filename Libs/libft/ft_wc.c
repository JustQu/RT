/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 16:37:51 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 16:38:11 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** count words in s
*/

unsigned int	ft_wc(char const *s)
{
	unsigned int wc;

	wc = 0;
	while (*s && ft_isspace(*s))
		s++;
	while (*s)
	{
		while (*s && !ft_isspace(*s))
			s++;
		wc++;
		while (*s && ft_isspace(*s))
			s++;
	}
	return (wc);
}
