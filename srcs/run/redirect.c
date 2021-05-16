/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:58 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:04:59 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in(t_token *token, int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	rd_fds[0] = open(token->arg, O_RDONLY);
	if (rd_fds[0] == -1)
		return (ft_print_err(token->arg, strerror(errno), NULL, 1));
	dup2(rd_fds[0], STDIN_FILENO);
	return (1);
}

static void	redirect_out(t_token *token, int *rd_fds)
{
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
	if (token->type == RD_OUT)
		rd_fds[1] = \
		open(token->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == RD_APPEND)
		rd_fds[1] = \
		open(token->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(rd_fds[1], STDOUT_FILENO);
}

int			redirect_process(t_token *token, int *rd_fds)
{
	rd_fds[0] = 0;
	rd_fds[1] = 0;
	while (token)
	{
		if (token->type == RD_IN)
		{
			if (!redirect_in(token, rd_fds))
				return (0);
		}
		else if (token->type == RD_OUT || token->type == RD_APPEND)
			redirect_out(token, rd_fds);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	while (token->prev)
		token = token->prev;
	return (1);
}

void		redirect_close(int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
}

void		redirect_restore(int *rd_fds, int *old_fds)
{
	if (rd_fds[0] > 0)
	{
		dup2(old_fds[0], STDIN_FILENO);
		close(rd_fds[0]);
		close(old_fds[0]);
	}
	if (rd_fds[1] > 0)
	{
		dup2(old_fds[1], STDOUT_FILENO);
		close(rd_fds[1]);
		close(old_fds[1]);
	}
}
