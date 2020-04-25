#include "rt.h"
#define BUFF_SIZE 128

/**
** @TODO(dmelessa): rewrite this one?
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

static const char const *files[] = {
	"world.h",
	"cl_rt.h",
	"utils.cl",
	"solver.cl",
	"random.cl",
	"color.cl",
	"sampler.cl",
	"sampler_manager.cl",
	"camera.cl",
	"intersection.cl",
	"normal.cl",
	"light.cl",
	"ray_tracer.cl",
	"path_tracer.cl",
	"main_kernel.cl"
};
int num_files = sizeof(files) / sizeof(char *);

void create_source(char **source_buf)
{
	char *dir;
	int i;
	char	*s;

	i = 0;
	dir = DEFAULT_KERNEL_DIR;
	while (i < num_files)
	{
		s = ft_strjoin(dir, files[i]);
		source_buf[i] = get_source_buf(s);
		free(s);
		if (source_buf[i] == NULL)
		{
			s = ft_strjoin("./include/", files[i]);
			source_buf[i] = get_source_buf(s);
			free(s);
		}
		i++;
	}
}

cl_program create_program(cl_context context)
{
	cl_program program;
	char **source_buf;
	int ret;

	source_buf = (char **)malloc(sizeof(char *) * num_files);
	create_source(source_buf);
	printf("HERE\n");
	program = clCreateProgramWithSource(context, num_files,
										(const char **)source_buf, NULL, &ret);
	printf("STEP2\n");
	// p->program = program;
	// assert(!ret);
	// cl_error(p, &p->clp, ret);
	ft_clerror(ret);
	// a = ret;
	free(source_buf);//memory leak!
	return (program);
}
