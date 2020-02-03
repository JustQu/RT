#include "../includes/rt.h"

char		*get_source_buf(char *file_name, size_t *size)
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
	*size = ft_strlen(source);
	return (source);
}

void		get_files_buf(char **source_buf, size_t *source_size)
{
	source_buf[0] = get_source_buf("source_cl/defines.cl", &source_size[0]);
	source_buf[1] = get_source_buf("source_cl/auxiliary.cl", &source_size[1]);
	source_buf[2] = get_source_buf("source_cl/figure_func.cl", &source_size[2]);
	source_buf[3] = get_source_buf("source_cl/calculate_clr.cl", &source_size[3]);
	source_buf[4] = get_source_buf("source_cl/kernel_main.cl", &source_size[4]);
}

cl_program	create_program(cl_context context)
{
	cl_program	program;
	char		**source_buf;
	size_t		*source_size;
	int			files_num;
	int			err;

	files_num = 5;
	source_buf = (char**)malloc(sizeof(char*) * files_num);
	source_size = (size_t*)malloc(sizeof(size_t) * files_num);
	get_files_buf(source_buf, source_size);
	program = clCreateProgramWithSource(context, files_num,
			(const char**)source_buf, (const size_t*)source_size, &err);
	ft_clerror(err);
	err = -1;
	while (++err < files_num)
		free(source_buf[err]);
	free(source_buf);
	free(source_size);
	return (program);
}