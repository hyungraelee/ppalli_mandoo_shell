#include "minishell.h"

char	*ft_strcpy_i_to_j(char *line, int i, int j)
{
	char	*result;
	int		k;

	if (!(result = (char *)malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	k = 0;
	while (i < j)
		result[k++] = line[i++];
	result[k] = '\0';
	return (result);
}
