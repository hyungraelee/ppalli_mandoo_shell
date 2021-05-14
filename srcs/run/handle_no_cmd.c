#include "minishell.h"

int handle_no_cmd(t_cmd *cmd_list, char ***envp)
{
	int rd_fds[2];
	int status;
	int old_fds[2];

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
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		g_global.pid = fork();
		if (g_global.pid == 0)
		{
			pipe_process(cmd_list);
			if (!redirect_process(cmd_list->token, rd_fds))
				exit(1);
			exit(0);
		}
		else if (g_global.pid == -1)
			ft_print_err("fork", strerror(errno), NULL, 1);
		else
		{
			wait(&status);
			g_global.exit = status >> 8;
			redirect_close(rd_fds);
			pipe_restore(cmd_list, old_fds);
		}
		return (1);
	}
	else
	{
		g_global.exit = 0;
		redirect_process(cmd_list->token, rd_fds);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
