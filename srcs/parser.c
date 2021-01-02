/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <cool.3meu@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:56:06 by aapricot          #+#    #+#             */
/*   Updated: 2020/12/13 15:45:09 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "offset.h"
#include "logs.h"
#include "resource_manager.h"
#include "scene.h"
#include "rt_error.h"

char		*delete_tabs(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = -1;
	i = 0;
	res = (char *)malloc(sizeof(char) * (char_count(str) + 1));
	rt_is_dead(system_err, system_malloc_error, !res, "");
	while (str[i] != '\0')
	{
		if (str[i] == '#')
		{
			i++;
			while (str[i] != '\0' && str[i] != '#')
				i++;
		}
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' &&
		str[i] != '#' && str[i] != '\0')
			res[++j] = str[i];
		if (str[i] != '\0')
			i++;
	}
	res[++j] = '\0';
	free(str);
	return (res);
}

char		*get_read_block(int fd)
{
	char	*cur_line;
	char	*block_line;
	char	*tmp;
	int		i;

	block_line = NULL;
	while ((i = get_next_line(fd, &cur_line)) == 1)
	{
		if (!ft_strcmp(cur_line, "\0") && block_line != NULL)
		{
			free(cur_line);
			break ;
		}
		if (block_line == NULL)
			block_line = ft_strdup(cur_line);
		else
		{
			tmp = block_line;
			block_line = ft_strjoin(tmp, cur_line);
			free(tmp);
		}
		rt_is_dead(system_err, system_malloc_error, !block_line, "");
		free(cur_line);
	}
	return (block_line);
}

void		pars_router(t_res_mngr *resource_manager, t_parsed_info *asset,
						char *block, int log)
{
	int		block_type;

	block_type = get_block_type(block);
	if (block_type == object)
		pars_object(resource_manager, asset, block, log);
	else if (block_type == light)
		pars_light(block, asset, resource_manager, log);
	else if (block_type == camera)
		pars_camera(block, &resource_manager->scene->camera, log);
	else if (block_type == options)
		pars_options(block, resource_manager);
	else if (block_type == 0)
		write_logs(UNKNOWN_SCENE_TYPE, log, block);
	else if (block_type == -1)
		write_logs(SCENE_TYPE_DOES_NOT_EXIST, log, block);
	write_logs(WRITE_BLOCK, log, block);
}

void		parser_cycle(t_res_mngr *resource_manager, t_parsed_info *asset,
						int fd, int log)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_read_block(fd)) != NULL)
	{
		line = delete_tabs(line);
		if ((i = check_brackets(line)) == 1)
			pars_router(resource_manager, asset, line, log);
		else if (i == -1)
			write_logs(BAD_BRACKETS, log, line);
		free(line);
	}
}

int			parser(t_res_mngr *resource_manager, t_parsed_info *asset,
					char *file_name)
{
	int		fd;
	int		log;

	if (file_name == NULL)
		return (ERROR);
	log = get_log_fd(file_name);
	if (log == -1)
		return (ERROR);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (ERROR);
	parser_cycle(resource_manager, asset, fd, log);
	if (close(log))
		rt_warning("Warning! Could not close log file.");
	if (close(fd))
		rt_warning("Warning! Could not close log file.");
	return (0);
}
