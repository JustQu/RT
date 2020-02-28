#include "rt.h"

int		main(void)
{
	char	*line = "or( 1.130, -2.000, -100.17)";
	int		f;
	int		l;
	cl_float4	origin;

	if (!find_parentheses(line, "or", &f, &l))
	{
		printf("error\n");
		return (-1);
	}
	origin = get_vector(&f, &l, line);
	printf("(%f, %f, %f, %f)\n", origin.x, origin.y, origin.z, origin.w);
	return (0);
}
