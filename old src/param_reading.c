/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:40:45 by dwalda-r          #+#    #+#             */
/*   Updated: 2019/09/14 16:57:39 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static float	ft_getfnumber(char *str)
{
	float	num;
	int		sign;
	int		del;

	del = 10;
	num = 0;
	while (*str && ft_isspace(*str))
		str++;
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
	{
		num = num * del + *str - '0';
		str++;
	}
	str = *str == '.' ? str + 1 : str;
	while (*str != '\0' && ft_isdigit(*str))
	{
		num = num + ((float)(*str - '0')) / (float)del;
		del *= 10;
		str++;
	}
	return (num * sign);
}

void			read_vec3_param(char *str, t_vec3 v3param,
								char *param, t_vec3 v3def)
{
	char	*c;
	int		i;

	i = 0;
	vec3_copy(v3def, v3param);
	c = ft_strstr(str, param);
	if (c == NULL)
		return ;
	while (*c != '\0' && *c != '(')
		c++;
	if (*c != '\0')
		c++;
	while (*c != '\0' && *c != ')')
	{
		v3param[i++] = ft_getfnumber(c);
		while (*c != '\0' && *c != ',' && *c != ')')
			c++;
		if (*c != '\0')
			c++;
	}
}

float			read_fparam(char *str, char *param, float dfval)
{
	float	num;
	char	*c;

	c = (ft_strstr(str, param));
	if (c)
	{
		num = ft_getfnumber(c + ft_strlen(param) + 1);
		if (num != 0)
			return (num);
	}
	return (dfval);
}
