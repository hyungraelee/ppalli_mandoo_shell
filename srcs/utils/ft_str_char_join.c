/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_char_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:05:10 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:05:11 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_char_join(char *before, char c)
{
	int		len;
	char	*after;
	int		i;

	len = ft_strlen(before);
	if (c == '\n')
		return (before);
	else
	{
		after = (char *)malloc(sizeof(char) * (len + 2));
		i = -1;
		if (before == NULL)
			after[0] = c;
		else
		{
			while (before[++i])
				after[i] = before[i];
			after[i] = c;
			free(before);
		}
		after[len + 1] = '\0';
	}
	return (after);
}
