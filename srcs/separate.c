#include "minishell.h"

int		check_quote(char *line, int i, char c)
{
	int	s_quote;
	int	d_quote;

	i++;
	s_quote = OFF;
	d_quote = OFF;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (s_quote == OFF)
				s_quote = ON;
			else if (s_quote == ON)
				s_quote = OFF;
		}
		else if (line[i] == '\"')
		{
			if (i == 0 || (d_quote == OFF && line[i - 1] != '\\'))
				d_quote = ON;
			else if (d_quote == ON && line[i - 1] != '\\')
				d_quote = OFF;
		}
		if (line[i] == c && (d_quote == OFF && s_quote == OFF))
			return (i);
		i++;
	}
	return (i);
}

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

char	**sep_cmdline(char *line)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		cnt;

	i = 0;
	j = -1;
	cnt = 0;
	while (line[i])
	{
		j = check_quote(line, j, ';');
		i = j;
		cnt++;
	}
	if (!(result = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	result[cnt] = NULL;
	i = 0;
	j = -1;
	k = 0;
	while (result[k])
	{
		j = check_quote(line, j, ';');
		result[k] = ft_strcpy_i_to_j(line, i, j);
		i = j + 1;
		k++;
	}
	return (result);
}
