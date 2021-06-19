/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:53 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:00:54 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *dp;
	unsigned char *sp;

	if (!dest && !src)
		return (0);
	if (dest <= src)
	{
		dp = dest;
		sp = (unsigned char *)src;
		while (n-- > 0)
		{
			*dp++ = *sp++;
		}
	}
	else
	{
		dp = dest + n;
		sp = (unsigned char *)src + n;
		while (n-- > 0)
		{
			*--dp = *--sp;
		}
	}
	return (dest);
}
