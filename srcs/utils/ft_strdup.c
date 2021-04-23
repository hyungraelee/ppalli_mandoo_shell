#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	char	*temp;
	size_t	len;

	len = ft_strlen(s);
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	temp = result;
	while (len--)
		*temp++ = *s++;
	*temp = '\0';
	return (result);
}
