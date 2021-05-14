#include "minishell.h"

static int	pipe_no_cmd(t_cmd *cmd_list, int *rd_fds, int *old_fds)
{
	int status;

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

int			handle_no_cmd(t_cmd *cmd_list, char ***envp)
{
	int rd_fds[2];
	int old_fds[2];

	save_old_fds(old_fds);
	replace_env_in_arg(cmd_list, envp);
	if (is_pipe_exist(cmd_list))
		return (pipe_no_cmd(cmd_list, rd_fds, old_fds));
	else
	{
		g_global.exit = 0;
		redirect_process(cmd_list->token, rd_fds);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
