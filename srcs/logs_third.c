/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs_third.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 18:21:51 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/10 18:23:58 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "logs.h"

void		write_logs_10(int num_log, int fd, char *str)
{
	if (num_log == BAD_LIGHT_TYPE)
	{
		ft_putendl_fd(str, fd);
		ft_putendl_fd("Light type does not exist", fd);
	}
}
