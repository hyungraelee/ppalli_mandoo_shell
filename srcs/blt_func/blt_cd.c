#include "minishell.h"


int		exec_cd(t_cmd *cmd_list, char ***envp)
{
	char	dest[PATH_MAX + 1];
	int		i;
	t_token	*path;

	i = 0;
	while (i < PATH_MAX + 1)
		dest[i++] = 0;
	path = cmd_list->token->next;
	if (!path->arg || !ft_strcmp("~", path->arg) || !ft_strcmp("~/", path->arg))
	{
		find_env_value("HOME", envp);
	}
	else if (path->arg[0] == '~' && path->arg[1] == '/' && ft_strlen(path->arg) > 2)
	{

	}
	else if (!ft_strcmp("-", path->arg))
	{

	}
	else
	{

	}
}

int		blt_cd(t_cmd *cmd_list, char **envp)
{
	pid_t	pid;
	int		rd_fds[2];
	int		status;

	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list, rd_fds);
			exec_cd(cmd_list, &envp);
			exit(0);
		}
		else if (pid == -1)
			; // error
		else
		{
			wait(&status);
			redirect_close(cmd_list, rd_fds);
			pipe_close(cmd_list);
		}
		return (1);
	}
	else
		exec_cd(cmd_list, &envp);
	return (1);
}
