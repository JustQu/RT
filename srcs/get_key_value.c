/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:54:36 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 15:52:27 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "rt_error.h"

char				*get_key(char **str)
{
	char			*a;
	int				i;

	a = (char *)malloc(sizeof(char) * 256);
	rt_is_dead(system_err, system_malloc_error, !a, "get ket value 1");
	i = 0;
	while (**str != '=' && **str != '\0' && i < 255)
	{
		a[i] = **str;
		i++;
		*str += 1;
	}
	a[i] = '\0';
	if (**str != '\0')
		*str += 1;
	return (a);
}

int					bracket_cycle(char *b, char **str)
{
	int				i;
	int				count;

	count = 1;
	i = 0;
	*str += 1;
	while (**str != '\0' && i < 255)
	{
		if (**str == '{')
			count++;
		else if (**str == '}')
			count--;
		if (count == 0)
			break ;
		b[i] = **str;
		i++;
		*str += 1;
	}
	return (i);
}

char				*get_value(char **str)
{
	char			*b;
	int				i;

	b = (char *)malloc(sizeof(char) * 256);
	rt_is_dead(system_err, system_malloc_error, !b, "get ket value 2");
	i = 0;
	if (**str == '{')
		i = bracket_cycle(b, str);
	else
	{
		while (**str != ';' && **str != '}' && **str != '\0' && i < 255)
		{
			b[i] = **str;
			i++;
			*str += 1;
		}
	}
	if (**str != '\0')
		*str += 1;
	b[i] = '\0';
	return (b);
}

t_rt_options		get_default_options(void)
{
	t_rt_options	options;

	options.shadows = 1;
	options.depth = 1;
	return (options);
}
