#include "libft.h"

void	ft_swap_i(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_f(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
