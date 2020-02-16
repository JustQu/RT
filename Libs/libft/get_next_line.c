/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:14:05 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/28 16:41:17 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_get_fd(t_list **list, const int fd)
{
	t_list	*node;

	node = *list;
	while (node)
	{
		if (node->content_size == (size_t)fd)
			return (node);
		node = node->next;
	}
	node = ft_lstnew("\0", 1);
	node->content_size = fd;
	ft_lstadd(list, node);
	node = *list;
	return (node);
}

static int		write_line(t_list **node, char **line)
{
	char	*str;
	t_list	*pnode;

	pnode = *node;
	if (pnode->content == NULL)
		return (0);
	str = ft_strchr((char *)pnode->content, '\n');
	if (str && *str)
	{
		if (!(*line = ft_strndup((char *)pnode->content, str
			- (char *)pnode->content)) || !(str = ft_strdup(str + 1)))
			return (-1);
		ft_memdel(&pnode->content);
		pnode->content = str;
		return (1);
	}
	if (pnode->content && *(char *)pnode->content)
	{
		if (!(*line = ft_strdup((char *)pnode->content)))
			return (-1);
		ft_memdel(&pnode->content);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_list	*list;
	t_list			*node;
	int				size;
	char			*str;

	if ((fd < 0) || (line == NULL) || (BUFF_SIZE < 1))
		return (-1);
	node = ft_get_fd(&list, fd);
	while ((size = read(fd, buff, BUFF_SIZE)) != 0 && (size != -1))
	{
		buff[size] = 0;
		str = (char *)node->content;
		if (!(node->content = ft_strjoin((char *)node->content, buff)))
			return (-1);
		ft_strdel(&str);
		if (ft_strchr((char *)node->content, '\n'))
			break ;
	}
	if (size == -1)
		return (-1);
	return (write_line(&node, line));
}
