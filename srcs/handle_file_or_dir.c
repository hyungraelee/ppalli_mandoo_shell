#include "minishell.h"

int	check_stat(char	*cmd_name, char ***envp)
{
	struct stat	buf;

	cmd_name = get_env_value(cmd_name, *envp);
	if (stat(cmd_name, &buf) == -1)
	{
		ft_print_err(cmd_name, strerror(errno), NULL, 127);
		return (127);
	}
	if (S_ISDIR(buf.st_mode))
		ft_print_err(cmd_name, "is a directory", NULL, 126);
	else if (S_ISREG(buf.st_mode))
	{
		if (buf.st_mode & S_IXUSR)
			g_exit = 0;
		else
			ft_print_err(cmd_name, "Permission denied", NULL, 126);
	}
	return (g_exit);
}

int	handle_file_or_dir(t_cmd *cmd_list, char ***envp)
{
	pid_t	pid;
	int		status;
	int		rd_fds[2];
	int		old_fds[2];

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	while (cmd_list->token)
	{
		cmd_list->token->arg = get_env_value(cmd_list->token->arg, *envp);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list->token, rd_fds);
			check_stat(cmd_list->cmd_name, envp);
			exit(g_exit);
		}
		else if (pid == -1)
			ft_print_err("fork", strerror(errno), NULL, 1);
		else
		{
			wait(&status);
			g_exit = status >> 8;
			redirect_close(rd_fds);
			pipe_restore(cmd_list, old_fds);
		}
	}
	else
	{
		redirect_process(cmd_list->token, rd_fds);
		check_stat(cmd_list->cmd_name, envp);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
