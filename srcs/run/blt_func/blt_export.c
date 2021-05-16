/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:42 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 20:01:52 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_export(char *arg, int i, char *name, char ***envp)
{
	int		chk;
	char	*value;
	char	*new_var;

	new_var = NULL;
	value = set_export_value(arg, i, *envp);
	new_var = ft_strjoin(name, value, 0);
	chk = find_env_name(name, *envp);
	if (chk >= 0)
	{
		ft_strlcpy((*envp)[chk], new_var, ft_strlen(new_var) + 1);
		free_str(new_var);
	}
	else
		*envp = add_env(*envp, new_var);
	free_str(value);
}

int		handle_normal_export(char ***envp, char *arg, char *name)
{
	int		i;
	int		chk;

	i = 0;
	while (arg[i] && arg[i] != '=')
		name = ft_str_char_join(name, arg[i++]);
	chk = set_env_name(&name, *envp);
	if (chk == 0)
	{
		free_str(name);
		return (0);
	}
	else
		change_export(arg, i, name, envp);
	free_str(name);
	return (1);
}

int		export_type_arg(char *arg, char ***envp)
{
	char	*name;

	name = NULL;
	if (arg[0] == '=')
		return (0);
	else
	{
		if (!handle_normal_export(envp, arg, name))
			return (0);
	}
	return (1);
}

int		blt_export(t_token *token, char ***envp)
{
	if (!token->next)
		print_export(*envp);
	else
	{
		while (token)
		{
			if (token->type == ARGUMENT)
			{
				if (!export_type_arg(token->arg, envp))
					return (ft_print_err("export", ERR_MSG1, NULL, 1));
			}
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
	g_global.exit = 0;
	return (1);
}
