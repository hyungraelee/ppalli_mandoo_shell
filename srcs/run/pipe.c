#include "minishell.h"

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
