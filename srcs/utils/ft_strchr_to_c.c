#include "minishell.h"

int		ft_strchr_to_c(const char *s, int a, char *c)
{
	while (*s != a)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	*c = (char *)s;
	return (1);
}
