#include "minishell.h"

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
	while (path[++i])
	{
		path[i] = ft_strjoin(ft_strjoin(path[i], "/", 1), cmd_list->cmd_name, 1);
		if (!stat(path[i], &buf))
		{
			cmd_list->cmd_name = ft_strdup(path[i]);
			break ;
		}
	}
	// if (!path[i])
		// command not found
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (run_process(cmd_list, envp));
}

char	*get_env_value(char *arg, char **env)
{
	char	*env_name;
	char	*result;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	result = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			if (flag & S_QUOTE)						// if s_quote on
				flag ^= S_QUOTE;						// s_quote off
			else if (!(flag & D_QUOTE))				// if d_quote off
				flag |= S_QUOTE;						// s_quote on
		}
		else if (arg[i] == '\"')
		{
			if (flag & D_QUOTE)						// if d_quote on
			{
				if (arg[i - 1] != '\\')
					flag ^= D_QUOTE;					// d_quote off
			}
			else if (!(flag & S_QUOTE))				// if s_quote off
				flag |= D_QUOTE;						// d_quote on
		}
		else
		{
			if (flag & S_QUOTE)
			{
				while (flag & S_QUOTE)
				{
					result = ft_str_char_join(result, arg[i++]);
					if (arg[i] == '\'')
						flag |= S_QUOTE;
				}
			}
			else if (flag & D_QUOTE)
			{
				while (flag & D_QUOTE)
				{
					if (arg[i] == '\\')
					{
						if (arg[i + 1] == '\'' || arg[i + 1] == '\"' || arg[i + 1] == '\\' || arg[i + 1] == '`')
						{
							result = ft_str_char_join(result, arg[++i]);
							i++;
						}
						else
							result = ft_str_char_join(result, arg[i++]);
					}
					else if (arg[i] == '$')
					{
						if (arg[i - 1] == '\\')
							result = ft_str_char_join(result, arg[i++]);
						else
						{
							while (!ft_strchr(" \t\n\"\'\\", arg[i]))
							{
								// $HOME -> /Users/jkeum
							}
						}
					}
				}
			}
		}
		i++;
	}
}