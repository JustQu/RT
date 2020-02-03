/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfalkrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:07:56 by mfalkrea          #+#    #+#             */
/*   Updated: 2020/01/09 17:07:58 by mfalkrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	init_func(t_rt *rt)
{
	rt->obj_name[0] = ft_strdup("cne");
	rt->obj_name[1] = ft_strdup("cld");
	rt->obj_name[2] = ft_strdup("crl");
	rt->obj_name[3] = ft_strdup("pln");
	rt->obj_name[4] = ft_strdup("sph");
	rt->obj_name[5] = ft_strdup("lgt");
	rt->num_obj = 0;
}

void	init_cam(char *line, t_rt *rt)
{
	int		i;

	i = 3;
	rt->cam.pnt = read_vec(line + i);
	i += next_num(line + i);
	rt->cam.dir = read_vec(line + i);
}

void	init_obj(char *line, t_rt *rt, int n)
{
	int		i;
	t_obj	*obj;

	i = 3;
	obj = rt->obj + rt->num_obj;
	obj->type = n;
	obj->pnt = read_vec(line + i);
	i += next_num(line + i);
	obj->dir = read_vec(line + i);
	i += next_num(line + i);
	obj->r = ft_atoi_float(line + i);
	i += next_num(line + i) + 2;
	obj->clr = ft_atoi_base(line + i, 16);
	i += next_num(line + i);
	obj->dif = ft_atoi_float(line + i);
	i += next_num(line + i);
	obj->ref = ft_atoi_float(line + i);
	rt->num_obj += 1;
}

void	count(int fd, t_rt *rt)
{
	char	*line;
	int		gnl;
	int		i;

	i = -1;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		while (++i < NUM_OF_TYPES)
			if (ft_strncmp(line, rt->obj_name[i], 3) == 0)
				rt->num_obj += 1;
		i = -1;
		free(line);
	}
	if (gnl == -1)
	{
		ft_putendl("unable to open file");
		exit(0);
	}
	rt->obj = malloc(sizeof(t_obj) * rt->num_obj);
	rt->num_obj = 0;
	close(fd);
}

void	init_scene(t_rt *rt)
{
	char	*line;
	int		fd;
	int		gnl;
	int		i;

	i = -1;
	init_func(rt);
	count(fd_return(rt->name), rt);
	fd = fd_return(rt->name);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (ft_strncmp(line, "cam", 3) == 0)
			init_cam(line, rt);
		while (++i < NUM_OF_TYPES)
			if (ft_strncmp(line, rt->obj_name[i], 3) == 0)
				init_obj(line, rt, i);
		i = -1;
		free(line);
	}
	if (gnl == -1)
		exit(0);
	close(fd);
}
