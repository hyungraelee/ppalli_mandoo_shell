/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:41 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:03:42 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_onoff(char *line, int *s_quote, int *d_quote, int i)
{
	if (*line == '\'')
	{
		if (*s_quote == OFF)
			*s_quote = ON;
		else if (*s_quote == ON)
			*s_quote = OFF;
	}
	else if (*line == '\"')
	{
		if (i == 0 || (*d_quote == OFF && *(line - 1) != '\\'))
			*d_quote = ON;
		else if (*d_quote == ON && *(line - 1) != '\\')
			*d_quote = OFF;
	}
}

static int	check_quote(char *line, int i, char c)
{
	int	s_quote;
	int	d_quote;

	i++;
	s_quote = OFF;
	d_quote = OFF;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote_onoff(&(line[i]), &s_quote, &d_quote, i);
		if (line[i] == c && (d_quote == OFF && s_quote == OFF))
			return (i);
		i++;
	}
	return (i);
}

static int	count_to_separate(char *line, char c)
{
	int		cnt;
	int		i;
	int		j;

	i = 0;
	j = -1;
	cnt = 0;
	while (line[i])
	{
		j = check_quote(line, j, c);
		i = j;
		cnt++;
	}
	return (cnt);
}

char		**separate(char *line, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		cnt;

	if (line == NULL)
		return (NULL);
	cnt = count_to_separate(line, c);
	if (!(result = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	result[cnt] = NULL;
	i = 0;
	j = -1;
	k = 0;
	while (k < cnt)
	{
		j = check_quote(line, j, c);
		result[k] = ft_strcpy_i_to_j(line, i, j);
		i = j + 1;
		k++;
	}
	return (result);
}
