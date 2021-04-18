#include "minishell.h"

int		check_quote(char *line, int i)
{
	int	s_quote;
	int	d_quote;

	i++;
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
		if (line[i] == ';' && (d_quote == OFF && s_quote == OFF))
			return (i);
	}
	return (i);
}

char	**sep_cmdline(char *line)
{
	char	**result;
	int		i;
	int		j;
	
	i = 0;
	j = -1;
	while (line[i])
	{
		j = check_quote(line, j);
		i = j;
	}
}