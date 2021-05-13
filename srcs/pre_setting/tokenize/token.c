#include "minishell.h"

static void	handle_quotes(char *cmdline, char *flag, int *i)
{
	if (cmdline[*i] == '\"' && !(*flag & D_QUOTE))
	{
		*flag |= D_QUOTE;
		while (*flag & D_QUOTE)
		{
			(*i)++;
			if (cmdline[*i] == '\\')
				*i += 2;
			if (cmdline[*i] == '\"')
				*flag ^= D_QUOTE;
		}
	}
	else if (cmdline[*i] == '\'')
	{
		while (cmdline[++(*i)] != '\'')
			;
	}
}

static int	count_args(char *cmdline)
{
	int		i;
	int		cnt;
	char	flag;

	i = 0;
	cnt = 0;
	flag = 0;
	while (cmdline[i])
	{
		if (!ft_strchr(" \t\n><", cmdline[i]))
		{
			cnt++;
			while (!ft_strchr(" \t\n><", cmdline[i]))
			{
				handle_quotes(cmdline, &flag, &i);
				i++;
			}
		}
		else
			i++;
	}
	return (cnt);
}

t_token		*get_token_list(char *cmdline, char **cmd_name)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * (count_args(cmdline) + 1));
	if (!args)
		return (NULL);
	args = token_array(args, cmdline);
	return (make_token_list(args, cmd_name));
}
