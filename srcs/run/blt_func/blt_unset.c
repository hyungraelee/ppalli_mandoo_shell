/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:51 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 20:03:13 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		chk_valid_name_unset(char *arg, char **env_name)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		*env_name = ft_str_char_join(*env_name, arg[i]);
		if (arg[i] == '=')
		{
			free_str(*env_name);
			return (-1);
		}
	}
	return (i);
}

int		unset_arg(char *arg, char *env_name, char ***envp)
{
	int		i;
	int		chk;

	i = chk_valid_name_unset(arg, &env_name);
	if (i < 0)
		return (0);
	if (!arg[i])
	{
		chk = set_env_name(&env_name, *envp);
		if (chk == 0)
		{
			free_str(env_name);
			return (0);
		}
		else
		{
			chk = find_env_name(env_name, *envp);
			if (chk >= 0)
				*envp = delete_env(*envp, chk);
		}
	}
	free_str(env_name);
	return (1);
}

int		blt_unset(t_token *token, char ***envp)
{
	char	*env_name;

	while (token)
	{
		if (token->type == ARGUMENT)
		{
			env_name = NULL;
			if (!unset_arg(token->arg, env_name, envp))
				return (ft_print_err("unset", ERR_MSG1, NULL, 1));
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	g_global.exit = 0;
	return (1);
}
