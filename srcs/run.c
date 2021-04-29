#include "minishell.h"

char	**make_args(t_token *token)
{
	char	**result;
	int		cnt;
	int		i;

	cnt = 0;
	while (token)
	{
		if (token->type == COMMAND || token->type == OPTION || token->type == STR)
			cnt++;
		else if (token->type == ENV)
		{
			cnt++;
			token->arg = getenv(token->arg);
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	while (token->prev)
		token = token->prev;
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (token)
	{
		if (token->type == COMMAND || token->type == OPTION || token->type == STR || token->type == ENV)
			result[i++] = ft_strdup(token->arg);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	result[i] = NULL;
	while (token->prev)
		token = token->prev;
	return (result);
}

void	redirect_process(t_token *token, int *rd_fds)
{
	rd_fds[0] = 0;
	rd_fds[1] = 0;
	while (token)
	{
		if (token->type == RD_IN)
		{
			if (rd_fds[0] > 0)
				close (rd_fds[0]);
			rd_fds[0] = open(token->arg, O_RDONLY);
			dup2(rd_fds[0], STDIN_FILENO);
		}
		else if (token->type == RD_OUT)
		{
			if (rd_fds[1] > 0)
				close (rd_fds[1]);
			rd_fds[1] = open(token->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(rd_fds[1], STDOUT_FILENO);
		}
		else if (token->type == RD_APPEND)
		{
			if (rd_fds[1] > 0)
				close (rd_fds[1]);
			rd_fds[1] = open(token->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(rd_fds[1], STDOUT_FILENO);
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	while (token->prev)
		token = token->prev;
}

void	redirect_close(int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
}

void	redirect_restore(int *rd_fds, int *old_fds)
{
	if (rd_fds[0] > 0)
	{
		dup2(old_fds[0], STDIN_FILENO);
		close(rd_fds[0]);
		close(old_fds[0]);
	}
	if (rd_fds[1] > 0)
	{
		dup2(old_fds[1], STDOUT_FILENO);
		close(rd_fds[1]);
		close(old_fds[1]);
	}
}

void	pipe_process(t_cmd *cmd_list)
{
	if (cmd_list->next || cmd_list->prev)
	{
		if (cmd_list->next && !cmd_list->prev)
			dup2(cmd_list->fds[1], STDOUT_FILENO);
		else if (cmd_list->next && cmd_list->prev)
		{
			dup2(cmd_list->fds[1], STDOUT_FILENO);
			dup2(cmd_list->prev->fds[0], STDIN_FILENO);
		}
		else if (!cmd_list->next && cmd_list->prev)
			dup2(cmd_list->prev->fds[0], STDIN_FILENO);
	}
}

void	pipe_close(t_cmd *cmd_list)
{
	if (cmd_list->next || cmd_list->prev)
	{
		if (cmd_list->next && !cmd_list->prev)
		{
			close(cmd_list->fds[1]);
		}
		else if (cmd_list->next && cmd_list->prev)
		{
			close(cmd_list->prev->fds[0]);
			close(cmd_list->fds[1]);
		}
		else if (!cmd_list->next && cmd_list->prev)
		{
			close(cmd_list->prev->fds[0]);
			close(cmd_list->fds[1]);
			close(cmd_list->fds[0]);
		}
	}
}

int	run_process(t_cmd *cmd_list, char **envp)
{
	char	**args;
	pid_t	pid;
	int		status;
	int		rd_fds[2];

	args = make_args(cmd_list->token);
	pipe(cmd_list->fds);
	pid = fork();
	if (pid == 0)
	{
		pipe_process(cmd_list);
		redirect_process(cmd_list->token, rd_fds);	// need error handle -> open error
		execve(cmd_list->cmd_name, args, envp);
		exit(0);
		// need error handle -> if execve error return -1
	}
	else if (pid == -1)
	{
		; // need error handle -> if fork error pid -1
	}
	else
	{
		wait(&status);
		redirect_close(rd_fds);
		pipe_close(cmd_list);
	}
	return (1);
}

int	run(t_cmd *cmd_list, char **envp)
{
	int	i;
	struct stat	buf;

	i = -1;
	while (cmd_list)
	{
		// while (++i < BLTIN_NUM)
		// 	if (!ft_strcmp(cmd_list->cmd_name, builtin_str(i)));
		// 		(*builtin_func(i))(cmd_list);
		if (!stat(cmd_list->cmd_name, &buf))
			run_process(cmd_list, envp);
		else
			find_cmd_path(cmd_list, envp);
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break ;
	}
	return (1);
}
