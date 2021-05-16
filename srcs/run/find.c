/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:12 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:00:13 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}

int		cmd_path_error(char *cmd_name, char **path, struct stat buf, int i)
{
	if (!stat(cmd_name, &buf) && S_ISDIR(buf.st_mode))
	{
		ft_print_err(cmd_name, ERR_MSG2, NULL, 126);
		free_double_arr(path);
		return (0);
	}
	if (!path || !path[i])
	{
		if (ft_strchr(cmd_name, '/') || !path)
			ft_print_err(cmd_name, ERR_MSG8, NULL, 127);
		else
			ft_print_err(cmd_name, ERR_MSG9, NULL, 127);
		free_double_arr(path);
		return (0);
	}
	if (!(buf.st_mode & S_IXUSR))
	{
		ft_print_err(cmd_name, ERR_MSG3, NULL, 126);
		free_double_arr(path);
		return (0);
	}
	return (1);
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
			free(cmd_list->cmd_name);
			cmd_list->cmd_name = ft_strdup(path[i]);
			break ;
		}
	}
	if (!cmd_path_error(cmd_list->cmd_name, path, buf, i))
		return (0);
	else
		free_double_arr(path);
	return (run_process(cmd_list, &envp));
}
