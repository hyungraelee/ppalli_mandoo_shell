/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:23 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:04:24 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dir_home_default(char *path, char *arg, char ***envp)
{
	char	*env_value;

	env_value = find_env_value("HOME", *envp);
	if (!env_value)
	{
		if (!arg)
			return (ft_print_err("cd", ERR_MSG4, NULL, 1));
	}
	else
		ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
	return (1);
}

static int	dir_oldpwd(char *path, char ***envp)
{
	char	*env_value;

	env_value = find_env_value("OLDPWD", *envp);
	if (!env_value)
		return (ft_print_err("cd", ERR_MSG5, NULL, 1));
	else
	{
		ft_putstr_fd(env_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
	}
	return (1);
}

int			handle_special_arg(char *path, char *arg, char ***envp)
{
	if (!arg || !ft_strcmp("~", arg) || !ft_strcmp("~/", arg))
	{
		if (!dir_home_default(path, arg, envp))
			return (0);
	}
	else if (!ft_strcmp("-", arg))
	{
		if (!dir_oldpwd(path, envp))
			return (0);
	}
	return (1);
}

void		dir_start_at_home(char *path, char *arg, char ***envp)
{
	int		i;
	int		j;
	char	*env_value;

	i = -1;
	j = 1;
	env_value = find_env_value("HOME", *envp);
	while (env_value[++i])
		path[i] = env_value[i];
	while (arg[j])
		path[i++] = arg[j++];
}
