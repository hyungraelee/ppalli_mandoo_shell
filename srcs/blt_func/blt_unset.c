#include "minishell.h"

char	**delete_env(char **envp, char *str, int idx)
{
	char	**result;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * i);
	if (!result)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		if (i != idx)
			result[i] = envp[i];
	}
	result[i] = NULL;
	free(str);
	return (result);
}

int		blt_unset(t_token *token, char ***envp)
{
	int		i;
	int		idx;
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
					;	//error (not a valid identifier)
				}
				else
				{
					idx = find_env_name(env_name, *envp);
					if (idx >= 0)
					{
						*envp = delete_env(*envp, env_name, idx);
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