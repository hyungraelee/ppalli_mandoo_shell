#include "minishell.h"

static char		*change_num(int n, int size, char *dst)
{
	char			chr;
	unsigned int	temp;

	dst[size] = '\0';
	if (n < 0)
	{
		temp = -n;
		while (size - 1 > 0)
		{
			chr = temp % 10 + '0';
			dst[size - 1] = chr;
			temp /= 10;
			size--;
		}
		dst[0] = '-';
	}
	else
		while (size - 1 >= 0)
		{
			chr = n % 10 + '0';
			dst[size - 1] = chr;
			n /= 10;
			size--;
		}
	return (dst);
}

static int		check_size(int n)
{
	int size;

	if (n == 0)
		return (1);
	if (n > 0)
		size = 0;
	else if (n < 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char	*result;
	int		size;

	size = check_size(n);
	if (!(result = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	result = change_num(n, size, result);
	return (result);
}
