/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:23:23 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:58 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_material	read_material(t_color dcolor)
{
	t_material	mat;

	mat.diff_color.color = dcolor.color;
	mat.kd = 0.8f;
	mat.ks = 0.2f;
	mat.n = 50.0f;
	return (mat);
}

int			read_all(int fd, t_param *p)
{
	char	*str;
	t_list	*list;

	list = NULL;
	while (get_next_line(fd, &str))
	{
		str = str_to_low(str);
		if (list == NULL)
			list = ft_lstnew(str, ft_strlen(str) + 1);
		else
			ft_lstadd(&list, ft_lstnew(str, ft_strlen(str) + 1));
		ft_strdel(&str);
	}
	if (fd < 0 || !list || !list_len(list, p))
		return (0);
	parse_list(p, list);
	ft_lstdel(&list, delete_lst);
	return (1);
}
