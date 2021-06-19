/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:25 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 17:59:26 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*make_cmd(char *cmdline)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = ft_strdup("");
	cmd->token = get_token_list(cmdline, &(cmd->cmd_name));
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*make_cmd_set(char **cmdlines)
{
	t_cmd	*list;
	t_cmd	*temp;
	int		i;

	i = 0;
	list = NULL;
	while (cmdlines[i])
	{
		temp = make_cmd(cmdlines[i]);
		if (!temp)
			return (NULL);
		if (list == NULL)
			list = temp;
		else
		{
			list->next = temp;
			temp->prev = list;
			list = list->next;
		}
		i++;
	}
	while (list->prev)
		list = list->prev;
	free_double_arr(cmdlines);
	return (list);
}

t_cmd	*get_parsed_list(char *cmd_set)
{
	char	**cmdlines;

	if (!cmd_set)
		return (NULL);
	cmdlines = separate(cmd_set, '|');
	if (!cmdlines)
		return (NULL);
	return (make_cmd_set(cmdlines));
}
