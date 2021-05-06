#include "minishell.h"

int	blt_env(t_token *token, char ***envp)
{
	int		i;
	int		j;
	char	*env_name;
	char	*env_value;

	while (token)
	{
		if (token->type == ARGUMENT)
			return (1);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	i = -1;
	while (*envp[++i])
	{
		j = 0;
		env_name = NULL;
		while (*envp[i][j] && *envp[i][j] != '=')
			env_name = ft_str_char_join(env_name, *envp[i][j++]);
		if (find_env_value(env_name, *envp))
		{
			ft_putstr_fd(env_name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			env_value = NULL;
			
		}
	}
}