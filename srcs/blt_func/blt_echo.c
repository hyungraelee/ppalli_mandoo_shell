#include "minishell.h"

void	exec_echo(t_cmd *cmd_list, char **envp)
{
	int		end_line;
	char	*env;

	end_line = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == OPTION)
		{
			if (!ft_strcmp(cmd_list->token->arg, "-n"))
				end_line = 1;
			else
				;
		}
		else if (cmd_list->token->type == STR)
			ft_putstr_fd(cmd_list->token->arg, STDOUT_FILENO);
		else if (cmd_list->token->type == ENV)
		{
			env = find_env_value(cmd_list->token->arg, envp);
			if (!env)
				;
			ft_putstr_fd(env, STDOUT_FILENO);
		}
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	if (end_line == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	blt_echo(t_cmd *cmd_list, char **envp)
{
	pid_t	pid;
	int		status;
	int		rd_fds[2];
	int		old_fds[2];

	pid = 1;
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list, rd_fds);
			exec_echo(cmd_list, envp);
			exit(0);
		}
		else if (pid == -1)
		{
			;
		}
		else
		{
			wait(&status);
			redirect_close(cmd_list, rd_fds);
			pipe_close(cmd_list);
		}
	}
	else
	{
		old_fds[0] = dup(STDIN_FILENO);
		old_fds[1] = dup(STDOUT_FILENO);
		redirect_process(cmd_list, rd_fds);
		exec_echo(cmd_list, envp);
		redirect_restore(cmd_list, rd_fds, old_fds);
	}
	return (1);
}
