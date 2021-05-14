#include "minishell.h"

void	replace_env_in_arg(t_cmd *cmd_list, char ***envp)
{
	while (cmd_list->token)
	{
		cmd_list->token->arg = get_env_value(cmd_list->token->arg, *envp);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
}
