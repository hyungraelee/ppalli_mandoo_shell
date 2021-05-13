#include "minishell.h"

void	print_export_value(char *envp, int idx, int fd)
{
	int		flag;
	char	*result;

	flag = 0;
	result = NULL;
	if (!envp[idx])
		result = ft_strdup("");
	else if (envp[idx] == '=')
	{
		result = ft_str_char_join(result, envp[idx++]);
		result = ft_str_char_join(result, '\"');
		while (envp[idx])
		{
			if (envp[idx] == '\"' && !(flag & S_QUOTE))
			{
				if (flag & D_QUOTE)
					flag ^= D_QUOTE;
				else
					flag |= D_QUOTE;
				idx++;
			}
			else if (envp[idx] == '\'' && !(flag & D_QUOTE))
			{
				if (flag & S_QUOTE)
					flag ^= S_QUOTE;
				else
					flag |= S_QUOTE;
				idx++;
			}
			else if (envp[idx] == '\\')
			{
				if (flag == 0)
				{
					idx++;
					if (envp[idx] == '\"' || envp[idx] == '\\' || envp[idx] == '`' || envp[idx] == '$')
					{
						result = ft_str_char_join(result, '\\');
						result = ft_str_char_join(result, envp[idx++]);
					}
					else
						result = ft_str_char_join(result, envp[idx++]);
				}
				else if (flag & D_QUOTE)
				{
					result = ft_str_char_join(result, envp[idx++]);
					if (envp[idx] == '\"' || envp[idx] == '\\' || envp[idx] == '`' || envp[idx] == '$')
						result = ft_str_char_join(result, envp[idx++]);
					else
					{
						result = ft_str_char_join(result, '\\');
						result = ft_str_char_join(result, envp[idx++]);
					}
				}
				else if (flag & S_QUOTE)
				{
					result = ft_str_char_join(result, '\\');
					result = ft_str_char_join(result, envp[idx++]);
				}
			}
			else
			{
				if (flag & S_QUOTE)
				{
					if (envp[idx] == '\"' || envp[idx] == '`' || envp[idx] == '$')
						result = ft_str_char_join(result, '\\');
				}
				result = ft_str_char_join(result, envp[idx++]);
			}
		}
		result = ft_str_char_join(result, '\"');
	}
	ft_putstr_fd(result, fd);
	free(result);
}

char	*set_export_value(char *arg, int idx, char **envp)
{
	int		i;
	int		flag;
	char	*result;
	char	*env_name;

	if (!arg)
		return (NULL);
	i = 0;
	flag = 0;
	result = NULL;
	while (arg[idx + i])
	{
		env_name = NULL;
		if (arg[idx + i] == '\"' && !(flag & S_QUOTE))
		{
			result = ft_str_char_join(result, arg[idx + i]);
			if (flag & D_QUOTE)
				flag ^= D_QUOTE;
			else
				flag |= D_QUOTE;
			i++;
		}
		else if (arg[idx + i] == '\'' && !(flag & D_QUOTE))
		{
			result = ft_str_char_join(result, arg[idx + i]);
			if (flag & S_QUOTE)
				flag ^= S_QUOTE;
			else
				flag |= S_QUOTE;
			i++;
		}
		else if (arg[idx + i] == '\\')
		{
			if (flag == 0 && arg[idx + i + 1] == '\'')
			{
				i++;
				result = ft_str_char_join(result, arg[idx + i++]);
			}
			else
			{
				result = ft_str_char_join(result, arg[idx + i]);
				i++;
				if (flag == 0 || flag & D_QUOTE)
				{
					if (arg[idx + i] == '\"' || arg[idx + i] == '$' || arg[idx + i] == '`' || arg[idx + i] == '\\')
						result = ft_str_char_join(result, arg[idx + i++]);
				}
			}
		}
		else if ((flag & S_QUOTE) && arg[idx + i] == '\"')
			result = ft_str_char_join(result, arg[idx + i++]);
		else if ((flag & D_QUOTE) && arg[idx + i] == '\'')
			result = ft_str_char_join(result, arg[idx + i++]);
		else if (!(flag & S_QUOTE) && arg[idx + i] == '$')
		{
			while (!ft_strchr(" \t\n$\"\'\\", arg[idx + (++i)]))
				env_name = ft_str_char_join(env_name, arg[idx + i]);
			result = ft_strjoin(result, find_env_value(env_name, envp), 1);
		}
		else
			result = ft_str_char_join(result, arg[idx + i++]);
		if (env_name)
			free(env_name);
	}
	return (result);
}

int		set_env_name(char **export_name, char **envp)
{
	int		i;
	char	*result;
	char	*key;

	i = 0;
	result = NULL;
	if ((*export_name)[0] != '$' && (*export_name)[0] != '_' && ft_isalpha((*export_name)[0]) == 0)
		return (0);	//error (not a valid identifier)
	while ((*export_name)[i])
	{
		if ((*export_name)[i] == '$')
		{
			key = NULL;
			while (!ft_strchr(" \t\n$\"\'\\=", (*export_name)[++i]))
				key = ft_str_char_join(key, (*export_name)[i]);
			if (find_env_name(key, envp) >= 0)
				result = ft_strjoin(result, set_export_value(find_env_value(key, envp), 0, envp), 1);
			if (key)
				free(key);
		}
		else
			result = ft_str_char_join(result, (*export_name)[i++]);
	}
	*export_name = result;
	if (!result || ft_isdigit(result[0]))
		return (0);	//error (not a valid identifier)
	i = -1;
	while (result[++i])
	{
		if (result[i] != '_' && ft_isalpha(result[i]) == 0)
			return (0);	//error (not a valid identifier)
	}
	return (1);
}
