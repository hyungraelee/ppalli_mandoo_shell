/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:44 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:03:45 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_flag_onoff(char *cmdline, int *index, int *flag)
{
	if (cmdline[index[0]] == '<')
		*flag |= RD_IN;
	else if (cmdline[index[0]] == '>' && cmdline[index[0] + 1] != '>')
		*flag |= RD_OUT;
	else if (cmdline[index[0]] == '>' && cmdline[index[0] + 1] == '>')
	{
		*flag |= RD_APPEND;
		index[0]++;
	}
	index[0]++;
}

static void	handle_normal_letter(char *cmdline, int *index, int *flag)
{
	if (cmdline[index[1]] == '\"' && !(*flag & D_QUOTE))
	{
		*flag |= D_QUOTE;
		while (*flag & D_QUOTE)
		{
			index[1]++;
			if (cmdline[index[1]] == '\\')
				index[1] += 2;
			if (cmdline[index[1]] == '\"')
				*flag ^= D_QUOTE;
		}
	}
	else if (cmdline[index[1]] == '\'')
	{
		while (cmdline[++index[1]] != '\'')
			;
	}
	index[1]++;
}

static void	join_rd(char **args, int *index, int *flag)
{
	if (*flag & RD_IN)
	{
		args[index[2]] = ft_strjoin("<", args[index[2]], 2);
		*flag ^= RD_IN;
	}
	else if (*flag & RD_OUT)
	{
		args[index[2]] = ft_strjoin(">", args[index[2]], 2);
		*flag ^= RD_OUT;
	}
	else if (*flag & RD_APPEND)
	{
		args[index[2]] = ft_strjoin(">>", args[index[2]], 2);
		*flag ^= RD_APPEND;
	}
	index[2]++;
}

char		**token_array(char **args, char *cmdline)
{
	int index[3];
	int	flag;

	ft_memset(index, 0, sizeof(index));
	flag = 0;
	while (cmdline[index[0]])
	{
		if (!ft_strchr(" \t\n><", cmdline[index[0]]))
		{
			index[1] = index[0];
			while (!ft_strchr(" \t\n><", cmdline[index[1]]) \
			&& cmdline[index[1]])
				handle_normal_letter(cmdline, index, &flag);
			args[index[2]] = ft_strcpy_i_to_j(cmdline, index[0], index[1]);
			join_rd(args, index, &flag);
			if (!cmdline[index[1]])
				break ;
			index[0] = index[1];
		}
		else
			redirect_flag_onoff(cmdline, index, &flag);
	}
	args[index[2]] = NULL;
	return (args);
}
