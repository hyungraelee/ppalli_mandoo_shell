#include "minishell.h"

int		find_env_name(char *env_name, char **envp)
{
	int	i;
	int	env_len;

	i = -1;
	env_len = ft_strlen(env_name);
	while (envp[++i])
	{
		if (!ft_strncmp(env_name, envp[i], env_len))
		{
			if (!envp[i][env_len] || envp[i][env_len] == '=')
				return (i);
		}
	}
	return (-1);
}

char	*find_env_value(char *env_name, char **envp)
{
	int	i;
	int	env_len;

	i = -1;
	env_len = ft_strlen(env_name);
	while (envp[++i])
	{
		if (!ft_strncmp(env_name, envp[i], env_len))
		{
			if (envp[i][env_len] == '=')
				// return (ft_strdup(envp[i] + env_len + 1));
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}

int		find_cmd_path(t_cmd *cmd_list, char **envp)
{
	char		*env_value;
	char		**path;
	int			i;
	struct stat	buf;

	env_value = find_env_value("PATH", envp);
	path = ft_split(env_value, ':');
	i = -1;
	while (path && path[++i])
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 1), cmd_list->cmd_name, 1);
		if (!stat(path[i], &buf))
		{
			cmd_list->cmd_name = ft_strdup(path[i]);
			break ;
		}
	}
	if (!stat(cmd_list->cmd_name, &buf) && S_ISDIR(buf.st_mode))
	{
		ft_print_err(cmd_list->cmd_name, "is a directory", NULL, 126);
		return (0);
	}
	if (!path || !path[i])
	{
		if (ft_strchr(cmd_list->cmd_name, '/') || !path)
			ft_print_err(cmd_list->cmd_name, "No such file or directory", NULL, 127);
		else
			ft_print_err(cmd_list->cmd_name, "command not found", NULL, 127);
		return (0);
	}
	if (!(buf.st_mode & S_IXUSR))
	{
		ft_print_err(cmd_list->cmd_name, "Permission denied", NULL, 126);
		return (0);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (run_process(cmd_list, &envp));
}

char	*get_env_value(char *arg, char **envp)
{
	char	*env_name;
	char	*env_temp;
	char	*result;
	int		i;
	int		j;

	i = 0;
	result = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'')
				result = ft_str_char_join(result, arg[i++]);
			i++;
		}
		else if (arg[i] == '\"')
		{
			i++;
			while (arg[i] != '\"')
			{
				env_name = NULL;
				env_temp = NULL;
				if (arg[i] == '\\')
				{
					if (arg[i + 1] == '\"' || arg[i + 1] == '\\' || arg[i + 1] == '`' || arg[i + 1] == '$')
						result = ft_str_char_join(result, arg[++i]);
					else
						result = ft_str_char_join(result, arg[i]);
					i++;
				}
				else if (arg[i] == '$')
				{
					if (arg[i + 1] == '?')
					{
						result = ft_strjoin(result, ft_itoa(g_global.exit), 3);
						i += 2;
					}
					else
					{
						while (!ft_strchr(" \t\n$\"\'\\", arg[++i]))
							env_name = ft_str_char_join(env_name, arg[i]);
						env_temp = set_env_value(find_env_value(env_name, envp), 0);
						result = ft_strjoin(result, env_temp, 1);
					}
				}
				else
					result = ft_str_char_join(result, arg[i++]);
				if (env_name)
					free(env_name);
				if (env_temp)
					free(env_temp);
			}
			i++;
		}
		else
		{
			if (arg[i] == '$')
			{
				if (arg[i + 1] == '?')
				{
					result = ft_strjoin(result, ft_itoa(g_global.exit), 3);
					i += 2;
				}
				else
				{
					env_name = NULL;
					env_temp = NULL;
					while (!ft_strchr(" \t\n$\"\'\\", arg[++i]))
						env_name = ft_str_char_join(env_name, arg[i]);
					env_temp = set_env_value(find_env_value(env_name, envp), 0);
					j = 0;
					while (env_temp && env_temp[j])
					{
						if (env_temp[j] == ' ' || env_temp[j] == '\t' || env_temp[j] == '\n')
						{
							result = ft_str_char_join(result, ' ');
							while (env_temp[j] == ' ' || env_temp[j] == '\t' || env_temp[j] == '\n')
								j++;
						}
						else
						{
							result = ft_str_char_join(result, env_temp[j]);
							j++;
						}
					}
					if (env_name)
						free(env_name);
					if (env_temp)
						free(env_temp);
				}
			}
			else
				result = ft_str_char_join(result, arg[i++]);
		}
	}
	free(arg);
	return (result);
}
