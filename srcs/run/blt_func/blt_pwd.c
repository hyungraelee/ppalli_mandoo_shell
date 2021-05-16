/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:49 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 17:59:50 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_pwd(t_token *token, char ***envp)
{
	char	buf[PATH_MAX];
	char	*pwd;
	int		trash;

	trash = token->type;
	if (find_env_name("PWD", *envp) > 0)
	{
		pwd = ft_strjoin(ft_strdup(find_env_value("PWD", *envp)), "\n", 1);
		ft_putstr_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		getcwd(buf, PATH_MAX);
		ft_putstr_fd(buf, STDOUT_FILENO);
	}
	g_global.exit = 0;
	return (1);
}
