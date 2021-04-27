#include "minishell.h"

char	**make_args(t_cmd *cmd_list)
{
	char	**result;
	int		cnt;
	int		i;

	cnt = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == COMMAND || cmd_list->token->type == OPTION || cmd_list->token->type == STR)
			cnt++;
		else if (cmd_list->token->type == ENV)
		{
			cnt++;
			cmd_list->token->arg = getenv(cmd_list->token->arg);
		}
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == COMMAND || cmd_list->token->type == OPTION || cmd_list->token->type == STR || cmd_list->token->type == ENV)
			result[i++] = ft_strdup(cmd_list->token->arg);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	result[i] = NULL;
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	return (result);
}

int	run_process(t_cmd *cmd_list, char **envp)
{
	char	**args;
	pid_t	pid;
	int		status;

	args = make_args(cmd_list);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_list->cmd_name, args, envp);
	}
	else if (pid < 0)
	{
		;
	}
	else
		wait(&status);
}

int	run(t_cmd *cmd_list, char **envp)
{
	int	i;
	struct stat	buf;

	i = -1;
	while (cmd_list)
	{
		// while (++i < BLTIN_NUM)
		// 	if (!ft_strcmp(cmd_list->cmd_name, builtin_str(i)));
		// 		(*builtin_func(i))(cmd_list);
		if (!stat(cmd_list->cmd_name, &buf))
			run_process(cmd_list, envp);
		else
			find_cmd_path(cmd_list, envp);
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break ;
	}


// 	while (++i < BLTIN_NUM)
// 		if (!ft_strcmp())
	return (1);
}
