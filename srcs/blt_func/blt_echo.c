#include "minishell.h"

int		blt_echo(t_token *token, char ***envp)
{
	char	*result;
	int		new_line;

	result = NULL;
	new_line = 1;
	while (token->type != ARGUMENT)
	{
		token->arg = get_env_value(token->arg, *envp);
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
			token->arg = get_env_value(token->arg, *envp);
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
	return (1);
}
