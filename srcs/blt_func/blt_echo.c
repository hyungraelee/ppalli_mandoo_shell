#include "minishell.h"

void	exec_echo(t_token *token, char **envp)
{
	int		end_line;
	char	*env;

	end_line = 0;
	while (token)
	{
		if (token->type == OPTION)
		{
			if (!ft_strcmp(token->arg, "-n"))
				end_line = 1;
			else
				;
		}
		else if (token->type == STR)
		{
			if (token->blank == 1)
				ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(token->arg, STDOUT_FILENO);
		}
		else if (token->type == ENV)
		{
			env = find_env_value(token->arg, envp);
			if (!env)
				;
			ft_putstr_fd(env, STDOUT_FILENO);
		}
		if (token->next)
			token = token->next;
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
			redirect_process(cmd_list->token, rd_fds);
			exec_echo(cmd_list->token, envp);
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
			pipe_close(cmd_list);
		}
	}
	else
	{
		old_fds[0] = dup(STDIN_FILENO);
		old_fds[1] = dup(STDOUT_FILENO);
		redirect_process(cmd_list->token, rd_fds);
		exec_echo(cmd_list->token, envp);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
