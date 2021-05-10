#include "minishell.h"

void	free_minishell(char	*input_string, char **cmd_set)
{
	int	i;

	i = 0;
	free(input_string);
	while (cmd_set && cmd_set[i])
		free(cmd_set[i++]);
	if (cmd_set)
		free(cmd_set);
	cmd_set = NULL;
}

void	free_token(t_token *token)
{
	while (token->prev)
		token = token->prev;
	while (token)
	{
		free(token->arg);
		if (token->next)
		{
			token = token->next;
			free(token->prev);
		}
		else
		{
			free(token);
			break ;
		}
	}
}

void	free_cmdlist(t_cmd *cmd_list)
{
	while (cmd_list->prev)
		cmd_list = cmd_list->prev;
	while (cmd_list)
	{
		free(cmd_list->cmd_name);
		free_token(cmd_list->token);
		if (cmd_list->next)
		{
			cmd_list = cmd_list->next;
			free(cmd_list->prev);
		}
		else
		{
			free(cmd_list);
			break ;
		}
	}
}

void	minishell(char **envp)
{
	int 		status;
	char		*input_string;
	char		**cmd_set;
	t_cmd		*cmd_list;
	int			i;
	t_history	*last;

	status = 1;
	last = NULL;
	while (status)
	{
		prompt();
		input_string = read_cmd(&last);
		if (!ft_strcmp(input_string, "") || !check_syntax_err(input_string))
		{
			free(input_string);
			input_string = NULL;
			continue ;
		}
		cmd_set = separate(input_string, ';');
		i = 0;
		while (cmd_set && cmd_set[i])
		{
			cmd_list = get_parsed_list(cmd_set[i++]);
			status = run(cmd_list, &envp);
			free_cmdlist(cmd_list);
		}
		free_minishell(input_string, cmd_set);
	}
}

void	prompt(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (g_global.exit == 0)
		write(1, B_GREEN, ft_strlen(B_GREEN));
	else
		write(1, B_RED, ft_strlen(B_RED));
	write(1, buf, ft_strlen(buf));
	write(1, " > ", 3);
	write(1, C_RESET, ft_strlen(C_RESET));
}
