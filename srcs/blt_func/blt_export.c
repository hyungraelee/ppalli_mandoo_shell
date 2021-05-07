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
			result = ft_str_char_join(result, arg[idx + i]);
			i++;
			if (flag == 0 || flag & D_QUOTE)
			{
				if (arg[idx + i] == '\"')
					result = ft_str_char_join(result, arg[idx + i++]);
				else if (arg[idx + i] == '$')
					result = ft_str_char_join(result, arg[idx + i++]);
			}
		}
		else if (flag & S_QUOTE && arg[idx + i] == '\"')
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
	if ((*export_name)[0] == '$')
	{
		i++;
		key = NULL;
		while ((*export_name)[i] && (*export_name)[i] != '=')
			key = ft_str_char_join(key, (*export_name)[i++]);
		if (!key)
			return (0);	// error (not a valid identifier)
		if (find_env_name(key, envp))
			result = find_env_value(key, envp);
		else
		{
			free(key);
			return (0);	// error (not a valid identifier)
		}
		if (key)
			free(key);
	}
	else
	{
		if ((*export_name)[0] != '_' && ft_isalpha((*export_name)[0]) == 0)
			return (0);	// error (not a valid identifier)
		else
		{
			while ((*export_name)[i] && (*export_name)[i] != '=')
				result = ft_str_char_join(result, (*export_name)[i++]);
		}
	}
	*export_name = result;
	return (1);
}

void	print_export(char **envp)
{
	int		i;
	int		j;
	char	**export;
	char	*export_name;
	char	*tmp;

	i = 0;
	while (envp[i])
		i++;
	export = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		export[i] = ft_strdup(envp[i]);
	export[i] = NULL;
	i--;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(export[j], export[j + 1]) > 0)
			{
				tmp = export[j + 1];
				export[j + 1] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i--;
	}
	i = -1;
	while (export[++i])		// if a=abc
	{
		j = 0;
		export_name = NULL;
		while (export[i][j] && export[i][j] != '=')
			export_name = ft_str_char_join(export_name, export[i][j++]);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(export_name, STDOUT_FILENO);
		print_export_value(export[i], j, STDOUT_FILENO);		// ="abc"
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(export_name);
	}
}

int		blt_export(t_token *token, char ***envp)
{
	int		i;
	int		idx;
	char	*export_name;
	char	*export_value;
	char	*new_var;

	if (!token->next)
		print_export(*envp);
	else
	{
		while (token)
		{
			if (token->type == ARGUMENT)
			{
				if (token->arg[0] == '=')
					; // error;
				else
				{
					// make token->arg pretty	ex) a"=b"cd -> a=bcd (remove quote whcih wrapping '=')
					i = 0;
					export_name = NULL;
					while (token->arg[i] && token->arg[i] != '=')
						export_name = ft_str_char_join(export_name, token->arg[i++]);
					if (!set_env_name(&export_name, *envp))	// if a" "=abc -> 0		or		a=abc -> 1
						; // error (not a valid identifier)
					export_value = set_export_value(token->arg, i, *envp);
					new_var = ft_strjoin(export_name, export_value, 0);
					idx = find_env_name(export_name, *envp);	// check if envp-key already exists
					if (idx > 0)
						ft_strlcpy((*envp)[idx], new_var, ft_strlen(new_var) + 1);
					else
						*envp = add_env(*envp, new_var);
					if (export_name)
						free(export_name);
					if (export_value)
						free(export_value);
				}
			}
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
	return (1);
}
