/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:12:33 by dmelessa          #+#    #+#             */
/*   Updated: 2020/12/29 14:27:42 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "rt_error.h"
#include "libft.h"

int		init_image(t_image *const image, t_u32 w, t_u32 h, char *image_file)
{
	size_t	size;

	if (w == 0 || h == 0)
	{
		w = DEFAULT_IMAGE_WIDTH;
		h = DEFAULT_IMAGE_HEIGHT;
		rt_warning("Warning! Wrong resolution!\nResolution is set to 800x640");
	}
	image->width = w;
	image->height = h;
	size = w * h;
	image->pixels = (t_u32 *)ft_memalloc(size * sizeof(*image->pixels));
	ft_memset(image->pixels, 0, size * sizeof(*image->pixels));
	rt_is_dead(system_err, system_malloc_error, !image->pixels,
				"\timage pixels");
	image->rgb = (t_color *)ft_memalloc(size * sizeof(*image->rgb));
	ft_memset(image->rgb, 0, size * sizeof(*image->rgb));
	rt_is_dead(system_err, system_malloc_error, !image->pixels, "\trgb image");
	image->png_image = ft_strjoin(image_file, ".png");
	image->bmp_image = ft_strjoin(image_file, ".bmp");
	return (SUCCESS);
}
