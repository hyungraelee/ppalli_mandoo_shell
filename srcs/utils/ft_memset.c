#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n--)
		*p++ = c;
	return (s);
}