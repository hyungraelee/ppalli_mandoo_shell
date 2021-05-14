#include "minishell.h"

void	save_old_fds(int *old_fds)
{
	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
}
