/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:12 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:11:39 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_dir(char *dest, char ***envp)
{
	int		rt;
	char	*inner_env;
	char	*temp;
	char	buf[PATH_MAX];

	rt = chdir(dest);
	inner_env = NULL;
	if (rt == -1)
	{
		ft_print_err("cd", strerror(errno), NULL, 1);
		return ;
	}
	temp = find_env_value("PWD", *envp);
	getcwd(buf, PATH_MAX);
	inner_env = find_env_value("OLDPWD", *envp);
	if (!inner_env)
		*envp = add_env(*envp, ft_strjoin("OLDPWD=", temp, 0));
	else
		ft_strlcpy(find_env_value("OLDPWD", *envp), temp, ft_strlen(temp) + 1);
	ft_strlcpy(temp, buf, ft_strlen(buf) + 1);
	g_global.exit = 0;
}

static char	*get_cd_arg(t_token *token)
{
	while (token->type != ARGUMENT)
	{
		if (token->next)
			token = token->next;
		else
			break ;
	}
	if (token->type == ARGUMENT)
		return (ft_strdup(token->arg));
	else
		return (NULL);
}

static int	is_special_arg(char *arg)
{
	return (!arg || !ft_strcmp("~", arg) || \
	!ft_strcmp("~/", arg) || !ft_strcmp("-", arg));
}

int			blt_cd(t_token *token, char ***envp)
{
	char	path[PATH_MAX + 1];
	int		i;
	char	*arg;

	ft_memset(path, 0, sizeof(path));
	arg = get_cd_arg(token);
	i = -1;
	if (is_special_arg(arg))
	{
		if (!handle_special_arg(path, arg, envp))
			return (0);
	}
	else if (arg[0] == '~' && arg[1] == '/' && ft_strlen(arg) > 2)
		dir_start_at_home(path, arg, envp);
	else
	{
		while (arg[++i])
			path[i] = arg[i];
	}
	free_str(arg);
	arg = NULL;
	change_dir(path, envp);
	return (1);
}
