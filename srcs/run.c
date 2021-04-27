#include "minishell.h"

char	**make_args(t_cmd *cmd_list)
{
	char	**result;
	int		cnt;
	int		i;

	cnt = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == COMMAND || cmd_list->token->type == OPTION || cmd_list->token->type == STR)
			cnt++;
		else if (cmd_list->token->type == ENV)
		{
			cnt++;
			cmd_list->token->arg = getenv(cmd_list->token->arg);
		}
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == COMMAND || cmd_list->token->type == OPTION || cmd_list->token->type == STR || cmd_list->token->type == ENV)
			result[i++] = ft_strdup(cmd_list->token->arg);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	result[i] = NULL;
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
	return (result);
}

void	redirect_process(t_cmd *cmd_list, t_redirect *rd_fd)
{
	rd_fd->fd_in = 0;
	rd_fd->fd_out = 0;
	while (cmd_list->token)
	{
		if (cmd_list->token->type == RD_IN)
		{
			if (rd_fd->fd_in > 0)
				close (rd_fd->fd_in);
			rd_fd->fd_in = open(cmd_list->token->arg, O_RDONLY);
			dup2(rd_fd->fd_in, STDIN_FILENO);
		}
		else if (cmd_list->token->type == RD_OUT)
		{
			if (rd_fd->fd_out > 0)
				close (rd_fd->fd_out);
			rd_fd->fd_out = open(cmd_list->token->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(rd_fd->fd_out, STDOUT_FILENO);
		}
		else if (cmd_list->token->type == RD_APPEND)
		{
			if (rd_fd->fd_out > 0)
				close (rd_fd->fd_out);
			rd_fd->fd_out = open(cmd_list->token->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(rd_fd->fd_out, STDOUT_FILENO);
		}
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
}

void	redirect_close(t_cmd *cmd_list, t_redirect *rd_fd)
{
	if (rd_fd->fd_in > 0)
		close(rd_fd->fd_in);
	if (rd_fd->fd_out > 0)
		close(rd_fd->fd_out);
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
	char		**args;
	pid_t		pid;
	int			status;
	t_redirect	rd_fd;

	args = make_args(cmd_list);
	pipe(cmd_list->fds);
	pid = fork();
	if (pid == 0)
	{
		pipe_process(cmd_list);
		redirect_process(cmd_list, &rd_fd);
		execve(cmd_list->cmd_name, args, envp);
		exit(0);
	}
	else if (pid < 0)
	{
		;
	}
	else
	{
		wait(&status);
		redirect_close(cmd_list, &rd_fd);
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


// 	while (++i < BLTIN_NUM)
// 		if (!ft_strcmp())
	return (1);
}
