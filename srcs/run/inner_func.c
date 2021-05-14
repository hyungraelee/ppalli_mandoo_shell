#include "minishell.h"

static int	get_cnt_args(t_token *token)
{
	int	cnt;

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
	return (cnt);
}

static char	**make_args(t_token *token)
{
	char **result;
	int cnt;
	int i;

	cnt = get_cnt_args(token);
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

static void	run_process_in_child(t_cmd *cmd_list, char ***envp, char **args, int *rd_fds)
{
	int	rt;

	rt = 0;
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

static void	run_process_in_parents(t_cmd *cmd_list, char **args, int *rd_fds, int *old_fds)
{
	int	status;

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

int			run_process(t_cmd *cmd_list, char ***envp)
{
	char **args;
	int rd_fds[2];
	int old_fds[2];

	save_old_fds(old_fds);
	replace_env_in_arg(cmd_list, envp);
	args = make_args(cmd_list->token);
	pipe(cmd_list->fds);
	g_global.pid = fork();
	if (g_global.pid == 0)
		run_process_in_child(cmd_list, envp, args, rd_fds);
	else if (g_global.pid == -1)
		ft_print_err("fork", strerror(errno), NULL, 1);
	else
		run_process_in_parents(cmd_list, args, rd_fds, old_fds);
	return (1);
}
