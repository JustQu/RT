/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:06:26 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/21 17:24:35 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "logs.h"
#include "resource_manager.h"
#include "scene.h"
#include "rt_error.h"

void		to_lower(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = (char)ft_tolower(str[i]);
		i++;
	}
}

int			check_block_type(char *str)
{
	int		i;

	i = 0;
	to_lower(str);
	if (!ft_strcmp(str, "object"))
		i = object;
	else if (!ft_strcmp(str, "light"))
		i = light;
	else if (!ft_strcmp(str, "camera"))
		i = camera;
	else if (!ft_strcmp(str, "options"))
		i = options;
	free(str);
	return (i);
}

int			block_type_lengh(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '{' && str[i] != '=')
		i++;
	return (i);
}

int			get_block_type(char *str)
{
	int		i;
	char	*type;
	int		j;

	i = 0;
	j = 0;
	if (str[0] == '=' || str[0] == '{')
		return (-1);
	type = (char *)ft_memalloc(sizeof(char) * (block_type_lengh(str) + 1));
	rt_is_dead(system_err, system_malloc_error, !type, "");
	while (str[i] != '{' && str[i] != '=')
	{
		type[j] = str[i];
		i++;
		j++;
	}
	type[j] = '\0';
	return (check_block_type(type));
}

int			check_brackets(char *str)
{
	int		i;
	int		brackets;
	int		count;

	i = -1;
	count = 0;
	brackets = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '{')
		{
			brackets++;
			count++;
		}
		else if (str[i] == '}')
		{
			brackets++;
			count--;
		}
	}
	if (count != 0)
		return (-1);
	else if (count == 0 && brackets == 0)
		return (-2);
	return (1);
}
