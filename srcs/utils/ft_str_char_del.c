#include "minishell.h"

char	*ft_str_char_del(char *before)
{
	char	*after;
	int		len;
	int		i;

	if (!before)
		return (NULL);
	len = ft_strlen(before);
	after = (char *)malloc(sizeof(char) * len);
	if (!after)
		return (NULL);
	i = -1;
	while (++i < len - 1)
		after[i] = before[i];
	after[i] = '\0';
	free(before);
	return (after);
}
