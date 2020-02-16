/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:53:10 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 17:53:11 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isbase(int c, int base)
{
	if (ft_isdigit(c))
		return (c - '0' < base);
	if (ft_isalpha(c) && base > 10)
		return (c - 'a' + 10 < base);
	return (0);
}
