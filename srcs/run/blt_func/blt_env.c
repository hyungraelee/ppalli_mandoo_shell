#include "minishell.h"

int		turn_on_flag(int *flag, int quote, int i)
{
	if (*flag & quote)
		*flag ^= quote;
	else
		*flag |= quote;
	i++;
	return (i);
}

// int		check_backslash_env(int *flag, char *arg, int idx, int i)
// {
	
// }

char	*set_env_value(char *arg, int idx)
{
	int		i;
	int		flag;
	char	*result;

	if (!arg)
		return (NULL);
	i = 0;
	flag = 0;
	result = NULL;
	while (arg[idx + i])
	{
		if (arg[idx + i] == '\"' && !(flag & S_QUOTE))
			i = turn_on_flag(&flag, D_QUOTE, i);
		// {
		// 	if (flag & D_QUOTE)
		// 		flag ^= D_QUOTE;
		// 	else
		// 		flag |= D_QUOTE;
		// 	i++;
		// }
		else if (arg[idx + i] == '\'' && !(flag & D_QUOTE))
			i = turn_on_flag(&flag, S_QUOTE, i);
		// {
		// 	if (flag & S_QUOTE)
		// 		flag ^= S_QUOTE;
		// 	else
		// 		flag |= S_QUOTE;
		// 	i++;
		// }
		else if (arg[idx + i] == '\\')
		{
			if (flag == 0)
				result = ft_str_char_join(result, arg[idx + ++i]);
			else if (flag & D_QUOTE)
			{
				i++;
				if (arg[idx + i] != '\"' && arg[idx + i] != '\\' && arg[idx + i] != '`' && arg[idx + i] != '$')
					result = ft_str_char_join(result, '\\');
				result = ft_str_char_join(result, arg[idx + i]);
			}
			else if (flag & S_QUOTE)
				result = ft_str_char_join(result, arg[idx + i]);
			i++;
		}
		else
			result = ft_str_char_join(result, arg[idx + i++]);
	}
	return (result);
}

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
	while ((*envp)[++i])
	{
		j = 0;
		env_name = NULL;
		while ((*envp)[i][j] && (*envp)[i][j] != '=')
			env_name = ft_str_char_join(env_name, (*envp)[i][j++]);
		if (find_env_value(env_name, *envp))
		{
			ft_putstr_fd(env_name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			env_value = set_env_value((*envp)[i], ++j);
			ft_putstr_fd(env_value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(env_value);
		}
	}
	g_global.exit = 0;
	return (1);
}
