#include "minishell.h"

char **make_args(t_token *token)
{
	char **result;
	int cnt;
	int i;

	cnt = 0;
	while (token)
	{
		if (token->type == COMMAND || token->type == ARGUMENT)
			cnt++;
		if (token->next)
			token = token->next;
		else
			break;
	}
	while (token->prev)
		token = token->prev;
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (token)
	{
		if (token->type == COMMAND || token->type == ARGUMENT)
			result[i++] = ft_strdup(token->arg);
		if (token->next)
			token = token->next;
		else
			break;
	}
	result[i] = NULL;
	while (token->prev)
		token = token->prev;
	return (result);
}

int run_process(t_cmd *cmd_list, char ***envp)
{
	char **args;
	int status;
	int rd_fds[2];
	int old_fds[2];
	int rt;

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	while (cmd_list->token)
	{
		cmd_list->token->arg = get_env_value(cmd_list->token->arg, *envp);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	args = make_args(cmd_list->token);
	pipe(cmd_list->fds);
	g_global.pid = fork();
	rt = 0;
	if (g_global.pid == 0)
	{
		pipe_process(cmd_list);
		if (!redirect_process(cmd_list->token, rd_fds))
			exit(1);
		rt = execve(cmd_list->cmd_name, args, *envp);
		if (rt == -1)
		{
			ft_print_err(cmd_list->cmd_name, strerror(errno), NULL, 1);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (g_global.pid == -1)
		ft_print_err("fork", strerror(errno), NULL, 1);
	else
	{
		wait(&status);
		if (status >> 8 == 255)
			g_global.exit = 255;
		else if (status >> 8 != 0)
			g_global.exit = 1;
		else if (g_global.signal_on)
			g_global.exit = status + 128;
		else
			g_global.exit = 0;
		free_double_arr(args);
		redirect_close(rd_fds);
		pipe_restore(cmd_list, old_fds);
	}
	return (1);
}
