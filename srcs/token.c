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

int		count_args(char *cmdline)
{
	int		i;
	int		cnt;
	char	flag;

	i = 0;
	cnt = 0;
	flag = 0;
	while (cmdline[i])
	{
		if (!ft_strchr(IFS, cmdline[i]))
		{
			cnt++;
			while (!ft_strchr(IFS, cmdline[i]))
			{
				if (cmdline[i] == '\"' && !(flag & D_QUOTE))
				{
					flag |= D_QUOTE;
					while (flag & D_QUOTE)
					{
						i++;
						if (cmdline[i] == '\"' && cmdline[i - 1] != '\\')
							flag ^= D_QUOTE;
					}
				}
				else if (cmdline[i] == '\'')
				{
					while (cmdline[++i] != '\'')
						;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (cnt);
}

void	make_args(char **args, char *cmdline)
{
	int	i;
	int	j;
	int	k;
	int	flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while (cmdline[i])
	{
		if (!ft_strchr(IFS, cmdline[i]))
		{
			j = i;
			while (!ft_strchr(IFS, cmdline[j]) && cmdline[j])
			{
				if (cmdline[j] == '\"' && !(flag & D_QUOTE))
				{
					flag |= D_QUOTE;
					while (flag & D_QUOTE)
					{
						j++;
						if (cmdline[j] == '\"' && cmdline[i - 1] != '\\')
							flag ^= D_QUOTE;
					}
				}
				else if (cmdline[j] == '\'')
				{
					while (cmdline[++j] != '\'')
						;
				}
				j++;
			}
			args[k++] = ft_strcpy_i_to_j(cmdline, i, j);
			if (!cmdline[j])
				break ;
			i = j + 1;
		}
		else
			i++;
	}
	args[k] = NULL;
}

t_token	*make_tokenlist(char *cmdline, char **cmd_name)
{
	t_token	*token;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (count_args(cmdline) + 1));
	if (!args)
		return (NULL);
	make_args(args, cmdline);
}


// int	main()
// {
// 	char	**args;
// 	char	cmdline[] = "> file >file >file>file1 hi\"hello \' $HOME  \"hello -n   \'he    l l    o    \"     \'";
// 	int		cnt;
// 	int		i;

// 	cnt = count_args(cmdline);
// 	printf("%d\n", cnt);

// 	args = (char **)malloc(sizeof(char *) * (cnt + 1));
// 	make_args(args, cmdline);
// 	i = 0;
// 	while (args[i])
// 		printf("%s\n", args[i++]);
// }
