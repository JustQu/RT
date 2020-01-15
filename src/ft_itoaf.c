/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:06:03 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_itoaf(float val, int fdigits)
{
	char		*nnum;
	float		fpart;
	char		*fnum;
	char		*tmp;
	int			sign;

	sign = val < 0 && fabs(val) < 1 ? -1 : 1;
	nnum = ft_itoa((int)val);
	val = val < 0 ? -val : val;
	fpart = val - (int)val;
	fpart *= pow(10, fdigits);
	fpart += pow(10, fdigits);
	fnum = ft_itoa((int)fpart);
	tmp = ft_strjoin(".", fnum + 1);
	ft_strdel(&fnum);
	fnum = ft_strjoin(nnum, tmp);
	ft_strdel(&tmp);
	ft_strdel(&nnum);
	if (sign == -1)
	{
		tmp = ft_strjoin("-", fnum);
		ft_strdel(&fnum);
		return (tmp);
	}
	return (fnum);
}
