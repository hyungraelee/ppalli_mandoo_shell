#include "minishell.h"

void	exec_echo(t_token *token, char **envp)
{
	char	*result;
	int		new_line;

	result = NULL;
	new_line = 1;
	while (token->type != ARGUMENT)
	{
		token->arg = get_env_value(token->arg, envp);
		token = token->next;
	}
	if (!ft_strcmp(token->arg, "-n"))
	{
		new_line = 0;
		token = token->next;
	}
	while (token)
	{
		if (token->type == ARGUMENT)
		{
			token->arg = get_env_value(token->arg, envp);
			result = ft_strjoin(result, token->arg, 1);
		}
		if (token->next && token->next->type == ARGUMENT)
		{
			result = ft_strjoin(result, " ", 1);
			token = token->next;
		}
		else
			break ;
	}
	if (new_line)
		result = ft_strjoin(result, "\n", 1);
	ft_putstr_fd(result, STDOUT_FILENO);
}

int	blt_echo(t_cmd *cmd_list, char **envp)
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
			pipe_restore(cmd_list, old_fds);
		}
	}
	else
	{
		redirect_process(cmd_list->token, rd_fds);
		exec_echo(cmd_list->token, envp);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
