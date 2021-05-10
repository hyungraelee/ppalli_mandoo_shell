#include "minishell.h"

char	**make_args(t_token *token)
{
	char	**result;
	int		cnt;
	int		i;

	cnt = 0;
	while (token)
	{
		if (token->type == COMMAND || token->type == ARGUMENT)
			cnt++;
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
		if (token->type == COMMAND || token->type == ARGUMENT)
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

int	redirect_process(t_token *token, int *rd_fds)
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
			if (rd_fds[0] == -1)
				return (ft_print_err(token->arg, strerror(errno), NULL, 1));
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
	return (1);
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

void	pipe_restore(t_cmd *cmd_list, int *old_fds)
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
			dup2(old_fds[1], STDOUT_FILENO);
			close(cmd_list->prev->fds[0]);
			close(cmd_list->fds[1]);
			close(cmd_list->fds[0]);
		}
	}
}

int	handle_no_cmd(t_cmd *cmd_list, char ***envp)
{
	int		rd_fds[2];
	int		status;
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

void	blt_run(int i, t_cmd *cmd_list, char ***envp)
{
	int		status;
	int		rd_fds[2];
	int		old_fds[2];

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	if (ft_strcmp(cmd_list->cmd_name, "export") && ft_strcmp(cmd_list->cmd_name, "env"))
	{
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
	}
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		g_global.pid = fork();
		if (g_global.pid == 0)
		{
			pipe_process(cmd_list);
			if (!redirect_process(cmd_list->token, rd_fds))
				exit(1);
			(*builtin_func(i))(cmd_list->token, envp);
			exit(0);
		}
		else if (g_global.pid == -1)
			ft_print_err("fork", strerror(errno), NULL, 1);
		else
		{
			wait(&status);
			if (status >> 8 != 0)
				g_global.exit = status >> 8;
			redirect_close(rd_fds);
			pipe_restore(cmd_list, old_fds);
		}
	}
	else
	{
		if (!redirect_process(cmd_list->token, rd_fds))
		{
			redirect_restore(rd_fds, old_fds);
			return ;
		}
		(*builtin_func(i))(cmd_list->token, envp);
		redirect_restore(rd_fds, old_fds);
	}
}

int	run_process(t_cmd *cmd_list, char ***envp)
{
	char	**args;
	int		status;
	int		rd_fds[2];
	int		old_fds[2];
	int		rt;

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	// g_global.exit = 0;
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
	args = make_args(cmd_list->token);
	pipe(cmd_list->fds);
	g_global.pid = fork();
	rt = 0;
	if (g_global.pid == 0)
	{
		pipe_process(cmd_list);
		if (!redirect_process(cmd_list->token, rd_fds))
			exit(1);
		rt = execve(cmd_list->cmd_name, args, *envp);
		if (rt == -1)
		{
			ft_print_err(cmd_list->cmd_name, strerror(errno), NULL, 1);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (g_global.pid == -1)
		ft_print_err("fork", strerror(errno), NULL, 1);
	else
	{
		wait(&status);
		if (status >> 8 == 255)
			g_global.exit = 255;
		else if (status >> 8 != 0)
			g_global.exit = 1;
		else
			g_global.exit = 0;
		redirect_close(rd_fds);
		pipe_restore(cmd_list, old_fds);
	}
	return (1);
}

int	run(t_cmd *cmd_list, char ***envp)
{
	int			i;
	struct stat	buf;

	while (cmd_list)
	{
		cmd_list->cmd_name = get_env_value(cmd_list->cmd_name, *envp);
		if (!cmd_list->cmd_name)
			handle_no_cmd(cmd_list, envp);
		else if ((cmd_list->cmd_name[0] == '.' && cmd_list->cmd_name[1] == '/') || cmd_list->cmd_name[0] == '/')
			handle_file_or_dir(cmd_list, envp);
		else
		{
			i = -1;
			while (++i < BLTIN_NUM)
			{
				if (!ft_strcmp(cmd_list->cmd_name, builtin_str(i)))
				{
					blt_run(i, cmd_list, envp);
					break ;
				}
			}
			if (i >= BLTIN_NUM)
			{
				if (!stat(cmd_list->cmd_name, &buf))
					run_process(cmd_list, envp);
				else
					find_cmd_path(cmd_list, *envp);
			}
		}
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break ;
	}
	return (1);
}
