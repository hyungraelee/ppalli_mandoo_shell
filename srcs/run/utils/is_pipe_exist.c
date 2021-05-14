#include "minishell.h"

int	is_pipe_exist(t_cmd *cmd_list)
{
	return (cmd_list->prev || cmd_list->next);
}
