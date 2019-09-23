/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwalda-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:25:41 by dwalda-r          #+#    #+#             */
/*   Updated: 2018/12/28 18:54:30 by dwalda-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*k;
	t_list	*res;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	while ((k = f(lst)) == NULL)
		lst = lst->next;
	if ((k = ft_lstnew(k->content, k->content_size)) == NULL)
		return (NULL);
	if ((lst = lst->next) == NULL)
		return (k);
	start = k;
	while (lst)
	{
		if ((res = f(lst)) != NULL)
		{
			if ((k->next = ft_lstnew(res->content, res->content_size)) == NULL)
				return (NULL);
			k = k->next;
		}
		lst = lst->next;
	}
	return (start);
}
