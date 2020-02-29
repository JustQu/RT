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

cl_program	create_program(cl_context context)
{
	cl_program	program;
	char		*source_buf;
	int			ret;

	source_buf = get_source_buf(ft_strjoin(DEFAULT_KERNEL_DIR, DEFAULT_KERNEL_FILE));
	program = clCreateProgramWithSource(context, 1,
			(const char**)&source_buf, NULL, &ret);
	ft_clerror(ret);
	free(source_buf);
	return (program);
}
