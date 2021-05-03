#include "minishell.h"

void	exec_pwd(char **envp)
{
	char	*pwd;

	pwd = find_env_value("PWD", envp);
	ft_putstr_fd(pwd, STDOUT_FILENO);
}

int	blt_pwd(t_cmd *cmd_list, char **envp)
{
	pid_t	pid;
	int		status;
	int		rd_fds[2];
	int		old_fds[2];

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list->token, rd_fds);
			exec_pwd(envp);
			exit(0);
		}
		else if (pid == -1)
		{
			;
		}
		else
		{
			wait(&status);
			redirect_close(rd_fds);
			pipe_restore(cmd_list, old_fds);
		}
	}
	else
	{
		redirect_process(cmd_list->token, rd_fds);
		exec_pwd(envp);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}