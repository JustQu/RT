#include "rt.h"

int		find_parentheses(char *line, char *param, int *f, int *l)
{
	int		i;
	int		j;
	int		log;

	log = 0;
	*f = 0;
	while (line[*f] != '\0' && log == 0)
	{
		i = 0;
		if (line[*f] == param[i])
		{
			j = *f;
			while (param[i] != '\0' && line[j] == param[i])
			{
				i++;
				j++;
			}
			if (param[i] == '\0')
				log = 1;
		}
		*f += 1;
	}
	if (log == 0)
		return (0);
	while (line[*f] != '\0' && line[*f] != '(')
		*f += 1;
	*l = *f;
	while (line[*l] != '\0' && line[*l] != ')')
		*l += 1;
	if (line[*l] == '\0')
		return (0);
	return (1);
}

cl_float4	get_vector(int *f, int *l, char *line)
{
	cl_float4	vec;
	
	vec.w = 0;
	vec.x = get_number(f, l, line);
	vec.y = get_number(f, l, line);
	vec.z = get_number(f, l, line);
	return vec;
}

float		get_number(int *f, int *l, char *line)
{
	int		unit;
	int		mantissa;
	float	number;
	int		len = 0;

	*f += 1;
	unit = ft_atoi(line + *f);
	while ((line[*f] >= 9 && line[*f] <= 13) || line[*f] == ' ')
		*f += 1;
	if (line[*f] == '-')
		*f += 1;
	while (line[*f] >= '0' && line[*f] <= '9')
		*f += 1;
	if (line[*f] == '.')
	{
		*f += 1;
		mantissa = ft_atoi(line + *f);
		while (line[*f] >= '0' && line[*f] <= '9')
		{
			*f += 1;
			len++;
		}
		number = (float)mantissa / pow(10, len);
		number =  (unit < 0) ? unit - number : unit + number;
		return number;
	}
	else
		return (float)unit;
}
