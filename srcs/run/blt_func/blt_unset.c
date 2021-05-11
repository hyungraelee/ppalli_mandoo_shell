#include "minishell.h"

char	**delete_env(char **envp, char *str, int idx)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * i);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != idx)
			result[j++] = envp[i++];
		else
			i++;
	}
	result[j] = NULL;
	// free(str);
	return (result);
}

int		blt_unset(t_token *token, char ***envp)
{
	int		i;
	int		idx;
	int		is_err;
	char	*env_name;

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
					return (ft_print_err("unset", "not a valid identifier", NULL, 1));
			}
			if (!token->arg[i])
			{
				is_err = set_env_name(&env_name, *envp);
				if (is_err == 0)
					return (ft_print_err("unset", "not a valid identifier", NULL, 1));
				else
				{
					idx = find_env_name(env_name, *envp);
					if (idx >= 0)
						*envp = delete_env(*envp, env_name, idx);
				}
			}
			if (env_name)
				free(env_name);
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	g_global.exit = 0;
	return (1);
}
