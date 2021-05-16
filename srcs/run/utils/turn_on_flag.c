/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_on_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:07 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:00:08 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		turn_on_flag(int *flag, int quote, int idx)
{
	if (*flag & quote)
		*flag ^= quote;
	else
		*flag |= quote;
	idx++;
	return (idx);
}
