#include "minishell.h"

int		chk_backslash_export(int *flag, char *arg, int idx, char **result)
{
	if (*flag == 0 && arg[idx + 1] == '\'')
	{
		idx++;
		*result = ft_str_char_join(*result, arg[idx++]);
	}
	else
	{
		*result = ft_str_char_join(*result, arg[idx++]);
		if (*flag == 0 || *flag & D_QUOTE)
		{
			if (arg[idx] == '\"' || arg[idx] == '$' ||
			arg[idx] == '`' || arg[idx] == '\\')
				*result = ft_str_char_join(*result, arg[idx++]);
		}
	}
	return (idx);
}

int		chk_squote_export_var(char *arg, int idx, char **envp, char **result)
{
	char	*env_name;

	env_name = NULL;
	while (!ft_strchr(" \t\n$\"\'\\", arg[++idx]))
		env_name = ft_str_char_join(env_name, arg[idx]);
	*result = ft_strjoin(*result, find_env_value(env_name, envp), 1);
	if (env_name)
		free(env_name);
	return (idx);
}

int		chk_other_cases_set(int *flag, char *arg, int idx, char **result)
{
	if (arg[idx] == '\\')
		idx = chk_backslash_export(flag, arg, idx, result);
	else if ((*flag & S_QUOTE) && arg[idx] == '\"')
		*result = ft_str_char_join(*result, arg[idx++]);
	else if ((*flag & D_QUOTE) && arg[idx] == '\'')
		*result = ft_str_char_join(*result, arg[idx++]);
	else
		*result = ft_str_char_join(*result, arg[idx++]);
	return (idx);
}

char	*set_export_value(char *arg, int idx, char **envp)
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
		{
			result = ft_str_char_join(result, arg[idx]);
			idx = turn_on_flag(&flag, D_QUOTE, idx);
		}
		else if (arg[idx] == '\'' && !(flag & D_QUOTE))
		{
			result = ft_str_char_join(result, arg[idx]);
			idx = turn_on_flag(&flag, S_QUOTE, idx);
		}
		else if (!(flag & S_QUOTE) && arg[idx] == '$')
			idx = chk_squote_export_var(arg, idx, envp, &result);
		else
			idx = chk_other_cases_set(&flag, arg, idx, &result);
	}
	return (result);
}
