#include "minishell.h"

int	read_cmd(char **line)
{
	int	c;

	*line = NULL;
	while (read(0, &c, sizeof(c)) > 0)
	{
		*line = ft_str_char_join(*line, c);
		if (c == '\n')
			break;
		c = 0;
	}
	return (1);
}
