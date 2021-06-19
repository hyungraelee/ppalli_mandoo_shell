/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_in_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:36 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:14:52 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_in_arg(t_cmd *cmd_list, char ***envp)
{
	while (cmd_list->token)
	{
		cmd_list->token->arg = get_env_value(cmd_list->token->arg, *envp);
		if (cmd_list->token->next)
			cmd_list->token = cmd_list->token->next;
		else
			break ;
	}
	while (cmd_list->token->prev)
		cmd_list->token = cmd_list->token->prev;
}
