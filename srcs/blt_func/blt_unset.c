#include "minishell.h"

int	blt_unset(t_token *token, char ***envp)
{
	int		i;
	int		is_err;
	char	*env_name;
	char	*env_value;
	char	*new_var;

	while (token)
	{
		if (token->type == ARGUMENT)
		{
			i = -1;
			env_name = NULL;
			while (token->arg[++i])
			{
				env_name = ft_str_char_join(env_name, token->arg[i]);
				if (token->arg[i] == '=')
				{
					env_value = set_env_value(set_export_value(token->arg, i, *envp), 0);
					new_var = ft_strjoin(env_name, env_value, 0);
					//print	//error (not a valid identifier)
					return (0);
				}
			}
			if (!token->arg[i])
			{
				is_err = set_env_name(&env_name, *envp);
				if (is_err == 0)
				{

				}
				else
				{
					if (find_env_name(env_name, *envp) >= 0)
					{
						 
					}
				}
			}
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	return (1);
}