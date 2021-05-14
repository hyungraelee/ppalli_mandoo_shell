#include "minishell.h"

int		chk_backslash_env(int *flag, char *arg, int idx, char **result)
{
	if (*flag == 0)
		*result = ft_str_char_join(*result, arg[++idx]);
	else if (*flag & D_QUOTE)
	{
		idx++;
		if (arg[idx] != '\"' && arg[idx] != '\\'
		&& arg[idx] != '`' && arg[idx] != '$')
			*result = ft_str_char_join(*result, '\\');
		*result = ft_str_char_join(*result, arg[idx]);
	}
	else if (*flag & S_QUOTE)
		*result = ft_str_char_join(*result, arg[idx]);
	idx++;
	return (idx);
}

char	*set_env_value(char *arg, int idx)
{
	int		flag;
	char	*result;

	if (!arg)
		return (NULL);
	flag = 0;
	result = NULL;
	while (arg[idx])
	{
		if (arg[idx] == '\"' && !(flag & S_QUOTE))
			idx = turn_on_flag(&flag, D_QUOTE, idx);
		else if (arg[idx] == '\'' && !(flag & D_QUOTE))
			idx = turn_on_flag(&flag, S_QUOTE, idx);
		else if (arg[idx] == '\\')
			idx = chk_backslash_env(&flag, arg, idx, &result);
		else
			result = ft_str_char_join(result, arg[idx++]);
	}
	return (result);
}

void	print_env(char *env_name, char **envp, int i, int j)
{
	char	*env_value;

	ft_putstr_fd(env_name, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	env_value = set_env_value(envp[i], j);
	ft_putstr_fd(env_value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(env_value);
}

int		chk_valid_cmd_env(t_token **token)
{
	while (token)
	{
		if ((*token)->type == ARGUMENT)
			return (0);
		if ((*token)->next)
			(*token) = (*token)->next;
		else
			break ;
	}
	return (1);
}

int		blt_env(t_token *token, char ***envp)
{
	int		i;
	int		j;
	char	*env_name;

	g_global.exit = 0;
	if (!chk_valid_cmd_env(&token))
		return (1);
	i = -1;
	while ((*envp)[++i])
	{
		j = 0;
		env_name = NULL;
		while ((*envp)[i][j] && (*envp)[i][j] != '=')
			env_name = ft_str_char_join(env_name, (*envp)[i][j++]);
		if (find_env_value(env_name, *envp))
			print_env(env_name, *envp, i, ++j);
		free_str(env_name);
	}
	return (1);
}
