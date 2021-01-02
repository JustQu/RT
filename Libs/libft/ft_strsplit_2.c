/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:19:59 by ageorgan          #+#    #+#             */
/*   Updated: 2020/06/29 00:09:03 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					is_it_space(const char *s, char *c)
{
	int				i;

	i = 0;
	while (c[i])
	{
		if (*s == c[i])
			return (1);
		++i;
	}
	return (0);
}

static int			numb_word(char const *s, char *c)
{
	int				num;

	num = 0;
	while (is_it_space(s, c))
		s++;
	if (!*s)
		return (num);
	if (*s != '\0')
		num++;
	while (!is_it_space(s, c) && *s != '\0')
		s++;
	if (*s != '\0')
		return (num + numb_word(s, c));
	else
		return (num);
}

static void			clear_mem(int i, char **arr)
{
	i--;
	while (i >= 0)
	{
		free((void*)arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

static char			**set_str(char **arr, char const *s, char *c, int n)
{
	size_t			len;
	unsigned int	start;
	int				i;

	i = 0;
	start = 0;
	len = 0;
	while (i < n)
	{
		while (is_it_space(&s[start + len], c))
			start++;
		while (!is_it_space(&s[start + len], c) && s[start + len])
			len++;
		arr[i] = ft_strsub(s, start, len);
		if (!arr[i])
		{
			clear_mem(i, arr);
			return (arr);
		}
		start += len;
		len = 0;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char				**ft_strsplit_2(char const *s, char *c)
{
	char			**arr;
	int				num;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	num = numb_word(s, c);
	if (!num)
		return (NULL);
	arr = (char**)malloc(sizeof(char**) * (num + 1));
	if (!arr)
		return (NULL);
	arr = set_str(arr, s, c, num);
	return (arr);
}
