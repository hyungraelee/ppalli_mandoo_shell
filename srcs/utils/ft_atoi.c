#include "minishell.h"

int	ft_atoi(const char *nptr)
{
	long long	res;
	int			issign;

	res = 0;
	issign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			issign *= (-1);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += (*nptr - '0');
		nptr++;
	}
	return ((int)(res * issign));
}
