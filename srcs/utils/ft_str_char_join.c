#include "minishell.h"

char	*ft_str_char_join(char *before, char c)
{
	int		len;
	char	*after;
	int		i;

	len = ft_strlen(before);
	after = (char *)malloc(sizeof(char) * (len + 2));
	i = -1;
	if (before == NULL)
		after[0] = c;
	else
	{
		while (before && before[++i])
			after[i] = before[i];
		after[i] = c;
		free(before);
	}
	after[len + 1] = '\0';
	return (after);
}
