#include "minishell.h"

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
		if (!ft_strchr(" \t\n><" , cmdline[i]))
		{
			cnt++;
			while (!ft_strchr(" \t\n><" , cmdline[i]))
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

char	**token_array(char **args, char *cmdline)
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
		if (!ft_strchr(" \t\n><" , cmdline[i]))
		{
			j = i;
			while (!ft_strchr(" \t\n><" , cmdline[j]) && cmdline[j])
			{
				if (cmdline[j] == '\"' && !(flag & D_QUOTE))
				{
					flag |= D_QUOTE;
					while (flag & D_QUOTE)
					{
						j++;
						if (cmdline[j] == '\"' && cmdline[j - 1] != '\\')
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
			args[k] = ft_strcpy_i_to_j(cmdline, i, j);
			if (flag & RD_IN)
			{
				args[k] = ft_strjoin("<", args[k], 2);
				flag ^= RD_IN;
			}
			else if (flag & RD_OUT)
			{
				args[k] = ft_strjoin(">", args[k], 2);
				flag ^= RD_OUT;
			}
			else if (flag & RD_APPEND)
			{
				args[k] = ft_strjoin(">>", args[k], 2);
				flag ^= RD_APPEND;
			}
			k++;
			if (!cmdline[j])
				break ;
			i = j;
		}
		else
		{
			if (cmdline[i] == '<')
				flag |= RD_IN;
			else if (cmdline[i] == '>' && cmdline[i + 1] != '>')
				flag |= RD_OUT;
			else if (cmdline[i] == '>' && cmdline[i + 1] == '>')
			{
				flag |= RD_APPEND;
				i++;
			}
			i++;
		}
	}
	args[k] = NULL;
	return (args);
}

t_token	*token_init(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->arg = NULL;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_token	*make_token(char *args, int command)
{
	t_token	*result;

	result = token_init();
	if (!result)
		return (0);
	if (args[0] == '<')
	{
		result->type = RD_IN;
		result->arg = ft_strtrim(args, "<");
	}
	else if (args[0] == '>' && args[1] != '>')
	{
		result->type = RD_OUT;
		result->arg = ft_strtrim(args, ">");
	}
	else if (args[0] == '>' && args[1] == '>')
	{
		result->type = RD_APPEND;
		result->arg = ft_strtrim(args, ">>");
	}
	else
	{
		if (command == 0)
			result->type = COMMAND;
		else
			result->type = ARGUMENT;
		result->arg = ft_strdup(args);
	}
	return (result);
}

t_token	*make_tokenlist(char *cmdline, char **cmd_name)
{
	t_token	*token;
	t_token	*temp;
	char	**args;
	int		i;
	int		command;

	args = (char **)malloc(sizeof(char *) * (count_args(cmdline) + 1));
	if (!args)
		return (NULL);
	args = token_array(args, cmdline);
	i = 0;
	command = 0;
	token = NULL;
	while (args[i])
	{
		temp = make_token(args[i], command);
		if (temp->type == COMMAND)
		{
			*cmd_name = ft_strjoin(*cmd_name, temp->arg, 1);
			command = 1;
		}
		if (!token)
			token = temp;
		else
		{
			token->next = temp;
			temp->prev = token;
			token = token->next;
		}
		free(args[i]);
		i++;
	}
	free(args);
	while (token->prev)
		token = token->prev;
	return (token);
}


// int	main()
// {
// 	char	**args;
// 	char	cmdline[] = "> file >file1 abc>file2>file3  def>>file4>>file5 hi\"hello \' $HOME  \"hello -n   \'he    l l    o    \"     \'   < inputfile";
// 	int		cnt;
// 	int		i;
// 	t_token	*token;
// 	char	*cmdname;

// 	token = make_tokenlist(cmdline, &cmdname);
// 	printf("cmdname = %s\n", cmdname);
// 	while (token)
// 	{
// 		printf("%d\n", token->type);
// 		printf("%s\n", token->arg);
// 		if (token->next)
// 			token = token->next;
// 		else
// 			break;
// 	}
// }
