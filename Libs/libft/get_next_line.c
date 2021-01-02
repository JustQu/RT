/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoor <jvoor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:27:23 by ageorgan          #+#    #+#             */
/*   Updated: 2020/12/29 15:35:32 by jvoor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*read_str(char *buff, int *ret, int fd)
{
	char			*t;
	char			p[BUFF_SIZE + 1];

	if ((*ret = read(fd, p, BUFF_SIZE)) == -1)
		return (NULL);
	p[*ret] = '\0';
	t = buff;
	buff = ft_strjoin(buff, p);
	ft_strdel(&t);
	return (buff);
}

char				*get(char *str, char **line, char *buff)
{
	char			*p;

	*str = '\0';
	*line = ft_strdup(buff);
	p = buff;
	buff = ft_strdup(str + 1);
	ft_strdel(&p);
	return (buff);
}

int					get_next_line(const int fd, char **line)
{
	int				ret;
	static char		*buff;
	char			*str;

	if (fd < 0 || !line)
		return (-1);
	ret = 1;
	if (!buff)
		buff = ft_strnew(0);
	while (ret > 0)
	{
		if ((str = ft_strchr(buff, '\n')) != NULL)
			return (!!(buff = get(str, line, buff)));
		if (!(buff = read_str(buff, &ret, fd)))
			return (-1);
	}
	if (ret == 0 && !ft_strlen(buff))
	{
		ft_memdel((void **)&buff);
		return (0);
	}
	*line = ft_strdup(buff);
	ft_strdel(&buff);
	return (1);
}
