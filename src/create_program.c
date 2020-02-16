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

void		get_files_buf(char **source_buf)
{
	char	*dir;
	char	*files[FILES_NUM];
	int		i;

	i = 0;
	dir = DEFAULT_KERNEL_DIR;
	files[0] = ft_strjoin(dir, DEFAULT_KERNEL_FILE);
	while (i < FILES_NUM)
	{
		source_buf[0] = get_source_buf(files[i]);
		i++;
	}
}

cl_program	create_program(cl_context context)
{
	cl_program	program;
	char		**source_buf;
	int			ret;

	source_buf = (char**)malloc(sizeof(char*) * FILES_NUM);
	get_files_buf(source_buf);
	program = clCreateProgramWithSource(context, FILES_NUM,
			(const char**)source_buf, NULL, &ret);
	assert(!ret);
	ret = -1;
	while (++ret < FILES_NUM)
		free(source_buf[ret]);
	free(source_buf);
	return (program);
}
