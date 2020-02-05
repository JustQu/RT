/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 04:43:17 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/06 08:51:02 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int t;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		t = -n;
	}
	else
		t = n;
	if (t / 10 == 0)
		ft_putchar_fd(t % 10 + '0', fd);
	else
	{
		ft_putnbr_fd(t / 10, fd);
		ft_putchar_fd(t % 10 + '0', fd);
	}
}
