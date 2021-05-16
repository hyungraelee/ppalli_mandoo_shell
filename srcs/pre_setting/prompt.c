/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:04:01 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:04:02 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (g_global.exit == 0)
		write(1, B_GREEN, ft_strlen(B_GREEN));
	else
		write(1, B_RED, ft_strlen(B_RED));
	write(1, buf, ft_strlen(buf));
	write(1, " > ", 3);
	write(1, C_RESET, ft_strlen(C_RESET));
}
