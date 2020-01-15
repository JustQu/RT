/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <dwalda-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:56:50 by dwalda-r          #+#    #+#             */
/*   Updated: 2020/01/15 11:22:50 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		list_len(t_list *l, t_param *p)
{
	size_t		len;
	size_t		lnum;
	t_obj_type	tp;

	lnum = 0;
	len = 0;
	while (l)
	{
		if ((tp = find_type(l)) == light)
		{
			lnum++;
			len++;
		}
		else if (tp != none && tp != camera)
			len++;
		l = l->next;
	}
	p->world.nlights = lnum;
	p->world.nobjs = len - lnum;
	if (lnum)
		p->world.lights = (t_light_source *)malloc(sizeof(t_light_source)
		* lnum);
	if (p->world.nobjs)
		p->world.objs = (t_obj *)malloc(sizeof(t_obj) * p->world.nobjs);
	return (len);
}

int			parse_list(t_param *p, t_list *l)
{
	t_obj_type	t;
	int			camflag;

	camflag = 0;
	while (l)
	{
		if ((t = find_type(l)) != none && t != camera)
			parse_obj(l, p, t);
		else if (!camflag && t == camera)
		{
			camflag = 1;
			init_camera(l, &(p->camera));
		}
		l = l->next;
	}
	if (!camflag)
		set_default_camera(&(p->camera));
	return (1);
}

void		delete_lst(void *s, size_t size)
{
	ft_memdel(&s);
	(void)size;
}
