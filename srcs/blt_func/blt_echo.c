#include "minishell.h"

int	blt_echo(t_cmd	*cmd_list)
{
	pid_t	pid;

	pid = 1;
	if (cmd_list->prev || cmd_list->next)
	{
		pid = fork();
		if (pid == 0)
		{

			exit(0);
		}
		else if (pid == -1)
		{

		}
		else
		{

		}
	}
	return (1);
}
