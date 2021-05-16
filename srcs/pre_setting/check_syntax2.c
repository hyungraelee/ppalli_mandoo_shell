/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:51 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:03:52 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	semicolon_flag_onoff(char input_string, int *i, char *sflag)
{
	if ((*sflag & REDIRECT) || (*sflag & PIPE))
		return (ft_print_synerr(input_string, 0));
	if (!(*sflag & CMD) && !(*sflag & POSSIBLE))
		return (ft_print_synerr(input_string, 0));
	*sflag = 0;
	(*i)++;
	return (1);
}

static int	pipe_flag_onoff(char input_string, int *i, char *sflag)
{
	if (*sflag & REDIRECT)
		return (ft_print_synerr(input_string, 0));
	if (!(*sflag & POSSIBLE) && !(*sflag & CMD))
		return (ft_print_synerr(input_string, 0));
	*sflag |= PIPE;
	*sflag &= ~(CMD + POSSIBLE);
	(*i)++;
	return (1);
}

static int	rd_flag_onoff(char *input_string, int *i, char *sflag, int *rd)
{
	if (*sflag & REDIRECT)
	{
		if (*input_string == '>' && *(input_string + 1) == '>')
			return (ft_print_synerr(*input_string, 3));
		else
			return (ft_print_synerr(*input_string, 0));
	}
	*sflag |= REDIRECT;
	if (*input_string == '>' && *(input_string + 1) == '>')
	{
		(*i) += 2;
		*rd = 3;
	}
	else if (*input_string == '>' && *(input_string + 1) != '>')
	{
		(*i)++;
		*rd = 2;
	}
	else
	{
		(*i)++;
		*rd = 1;
	}
	return (1);
}

int			handle_special_letter(char *input, int *i, char *sflag, int *rd)
{
	if (*input == '>' || *input == '<')
	{
		if (!rd_flag_onoff(input, i, sflag, rd))
			return (0);
	}
	else if (*input == '|')
	{
		if (!pipe_flag_onoff(*input, i, sflag))
			return (0);
	}
	else if (*input == ';')
	{
		if (!semicolon_flag_onoff(*input, i, sflag))
			return (0);
	}
	return (1);
}
