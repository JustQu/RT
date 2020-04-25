#include <stdlib.h>

float rand_float()
{
	return ((float)rand() / (float)RAND_MAX);
}

int	rand_int()
{
	return rand();
}
