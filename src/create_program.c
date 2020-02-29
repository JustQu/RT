#include "rt.h"
#define BUFF_SIZE 32

/**
** @TODO(dmelessa): rewrite this one
** @brief Get the source buf object
**
** @param file_name
** @return ** char*
*/
char		*get_source_buf(char *file_name)
{
	int		fd;
	char	*source;
	char	*tmp;
	int		ret;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	source = ft_strdup("");
	ret = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = source;
		source = ft_strjoin(source, buff);
		ft_strdel(&tmp);
	}
	if (ret < 0)
	{
		ft_strdel(&source);
		return (NULL);
	}
	close(fd);
	return (source);
}

void	create_source(char **source_buf, int num)
{
	char	*dir;
	char	*file_names[num];
	int		i;

	i = 0;
	dir = DEFAULT_KERNEL_DIR;
	file_names[0] = "solver.cl";
	file_names[1] = "object_intersection.cl";
	file_names[2] = "get_random.cl";
	file_names[3] = "get_point_color.cl";
	file_names[4] = DEFAULT_KERNEL_FILE;
	while (i < num)
	{
		source_buf[i] = get_source_buf(ft_strjoin(dir, file_names[i]));
		i++;
	}
}

cl_program	create_program(cl_context context)
{
	cl_program	program;
	char		**source_buf;
	int			ret;
	int			NUM_FILES;

	NUM_FILES = 5;
	source_buf = (char**)malloc(sizeof(char*) * NUM_FILES);
	create_source(source_buf, NUM_FILES);
	program = clCreateProgramWithSource(context, NUM_FILES,
			(const char**)source_buf, NULL, &ret);
	ft_clerror(ret);
	free(source_buf);
	return (program);
}
