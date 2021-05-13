#include "minishell.h"

int		unset_arg(char *arg, char *env_name, char ***envp)
{
	int		i;
	int		idx;
	int		is_err;

	i = -1;
	while (arg[++i])
	{
		env_name = ft_str_char_join(env_name, arg[i]);
		if (arg[i] == '=')
		{
			if (env_name)
				free(env_name);
			return (0);
		}
	}
	if (!arg[i])
	{
		is_err = set_env_name(&env_name, *envp);
		if (is_err == 0)
		{
			if (env_name)
				free(env_name);
			return (0);
		}
		else
		{
			idx = find_env_name(env_name, *envp);
			if (idx >= 0)
				*envp = delete_env(*envp, env_name, idx);
		}
	}
	if (env_name)
		free(env_name);
	return (1);
}

int		blt_unset(t_token *token, char ***envp)
{
	char	*env_name;

	while (token)
	{
		if (token->type == ARGUMENT)
		{
			env_name = NULL;
			if (!unset_arg(token->arg, env_name, envp))
				return (ft_print_err("unset", ERR_MSG1, NULL, 1));
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	g_global.exit = 0;
	return (1);
}
