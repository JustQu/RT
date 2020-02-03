/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfalkrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:08:31 by mfalkrea          #+#    #+#             */
/*   Updated: 2020/01/09 17:08:33 by mfalkrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			next_num(char *line)
{
	int		i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	while ((line[i] < 9 || line[i] > 13) && line[i] != ' ' && line[i] != '\0')
		i++;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	return (i);
}

int			ret_i(char *line)
{
	int		i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
		i++;
	i++;
	return (i);
}

float		ft_atoi_float(char *line)
{
	float	a;
	int		b;
	int		i;
	int		n;

	n = 0;
	a = ft_atoi(line);
	i = ret_i(line);
	if (line[i - 1] == '.')
	{
		b = ft_atoi(line + i);
		while (line[i + n] >= '0' && line[i + n] <= '9')
			n++;
		if (a >= 0)
			a += (float)b / pow(10, n);
		else
			a -= (float)b / pow(10, n);
	}
	return (a);
}

cl_float3	read_vec(char *line)
{
	cl_float3	ret;
	int			i;

	ret.x = ft_atoi_float(line);
	i = ret_i(line);
	if (line[i - 1] == '.')
		i += ret_i(line + i);
	ret.y = ft_atoi_float(line + i);
	i += ret_i(line + i);
	if (line[i - 1] == '.')
		i += ret_i(line + i);
	ret.z = ft_atoi_float(line + i);
	return (ret);
}
