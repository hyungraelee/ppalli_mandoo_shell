/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_char_embed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:05:08 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:05:09 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_char_embed(char *before, char c, int index)
{
	char	*after;
	int		len;
	int		i;

	if (!before)
		return (NULL);
	len = ft_strlen(before);
	after = (char *)malloc(sizeof(char) * (len + 2));
	if (!after)
		return (NULL);
	i = -1;
	while (++i < index)
		after[i] = before[i];
	after[i] = c;
	while (++i < len + 1)
		after[i] = before[i - 1];
	after[i] = '\0';
	free(before);
	return (after);
}
