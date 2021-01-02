/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:38:04 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/20 23:56:51 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#include "libft.h"

/*
** @brief allocate memory with size = `new_size`
** and copy `current_size` bytes data from `mem` memory
** @todo: move to libft
** @param mem
** @param current_size
** @param new_size
** @return ** void*
*/

void		*ft_realloc(void *mem, size_t current_size, size_t new_size)
{
	void	*new_mem;

	new_mem = malloc(new_size);
	if (new_mem == NULL)
		return (NULL);
	ft_memcpy(new_mem, mem, current_size);
	ft_memdel(&mem);
	return (new_mem);
}

float		float_min(float a, float b)
{
	return (a < b ? a : b);
}

float		float_max(float a, float b)
{
	return (a > b ? a : b);
}

int			int_max(int a, int b)
{
	return (a > b ? a : b);
}

int			int_min(int a, int b)
{
	return (a < b ? a : b);
}
