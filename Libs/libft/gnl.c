#include "stdio.h"
#include "string.h"

#include "libft.h"

#define BUFF_SIZE 512

static t_list	*get_fd(t_list **list, const int fd)
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

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_list	*list;
	t_list			*node;
	int				size;
	char			*str;

	if ((fd < 0) || (line == NULL) || (BUFF_SIZE < 1))
		return (-1);
}