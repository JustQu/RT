#include <stdio.h>

typedef struct	matrix
{
	int			**elements;
}				matrix;

void	new_matrix(matrix, int a, int b)
{
	matrix.elemets = malloc(sizeof(*elements) * a);
	if (!matrix.elements)
	{
		printf("Malloc error\n");
		exit(1);
	}

	for (int i = 0; i < a; i++)
	{
		matrix.elements[i] = malloc(sizeof(int) * b);
		if (!matrix.elements[i])
		{
			printf("Malloc error\n");
			exit(1);
		}
	}
}



int main()
{
}
