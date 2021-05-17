/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:33 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/17 14:22:35 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	if (str)
		free(str);
}

void	free_double_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_minishell(t_minishell *shell)
{
	int	i;

	i = 0;
	free(shell->input_str);
	while (shell->cmd_set && (shell->cmd_set)[i])
		free((shell->cmd_set)[i++]);
	if (shell->cmd_set)
		free(shell->cmd_set);
	shell->cmd_set = NULL;
}

void	free_token(t_token *token)
{
	while (token->prev)
		token = token->prev;
	while (token)
	{
		free(token->arg);
		if (token->next)
		{
			token = token->next;
			free(token->prev);
		}
		else
		{
			free(token);
			break ;
		}
	}
}

void	free_cmdlist(t_cmd *cmd_list)
{
	while (cmd_list->prev)
		cmd_list = cmd_list->prev;
	while (cmd_list)
	{
		free(cmd_list->cmd_name);
		free_token(cmd_list->token);
		if (cmd_list->next)
		{
			cmd_list = cmd_list->next;
			free(cmd_list->prev);
		}
		else
		{
			free(cmd_list);
			break ;
		}
	}
}
