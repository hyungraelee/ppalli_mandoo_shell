#include "minishell.h"

static int	count_size(char const *s, char c)
{
	int size;

	size = 0;
	while (*s && *s != c)
	{
		size++;
		s++;
	}
	return (size);
}

static int	count_word(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

static char	**free_arr(char **arr, int row)
{
	int i;

	i = 0;
	while (i <= row)
		free(arr[i]);
	free(arr);
	return (0);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		size;

	if (!s)
		return (0);
	if (!(result = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1))))
		return (0);
	i = 0;
	while (*s)
	{
		if (*s && *s != c)
		{
			size = count_size(s, c);
			if (!(result[i] = (char *)malloc(sizeof(char) * (size + 1))))
				return (free_arr(result, i - 1));
			ft_strlcpy(result[i++], s, size + 1);
			s += size;
		}
		else
			s++;
	}
	result[i] = 0;
	return (result);
}