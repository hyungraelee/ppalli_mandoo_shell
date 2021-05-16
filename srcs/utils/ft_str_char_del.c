/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_char_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:05:07 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:05:08 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_char_del(char *before, int index)
{
	char	*after;
	int		len;
	int		i;

	if (!before)
		return (NULL);
	len = ft_strlen(before);
	after = (char *)malloc(sizeof(char) * len);
	if (!after)
		return (NULL);
	i = -1;
	while (++i < index)
		after[i] = before[i];
	while (++i < len)
		after[i - 1] = before[i];
	after[len - 1] = '\0';
	free(before);
	return (after);
}
