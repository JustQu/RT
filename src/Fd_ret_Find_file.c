#include "rt.h"

void	unable_to_read_file(char *file_name)
{
	ft_putstr_fd("unable to read file: \'./", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\'\n", 2);
	exit(1);
}

int		fd_return(char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_putstr_fd("unable to open file: \'./", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\'\n", 2);
		exit(1);
	}
	return (fd);
}

char	*find_file_name(char *str)
{
	char	*name;
	int		first;
	int		last;
	int		i;

	i = 0;
	first = 0;
	while (str[first] != '\0' && str[first] != '"')
		first++;
	last = ++first;
	while (str[last] != '\0' && str[last] != '"')
		last++;
	name = malloc(sizeof(char) * (last - first + 1));
	while (first < last)
	{
		name[i] = str[first];
		first++;
		i++;
	}
	name[i] = '\0';
	return (name);
}
