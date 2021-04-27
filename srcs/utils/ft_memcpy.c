#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	temp = dest;
	s = src;
	while (n--)
		*temp++ = *s++;
	return (dest);
}
