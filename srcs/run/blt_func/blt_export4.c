/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:47 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 17:59:48 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		chk_backslash_flag_zero(char *envp, int idx, char **result)
{
	idx++;
	if (envp[idx] == '\"' || envp[idx] == '\\' ||
	envp[idx] == '`' || envp[idx] == '$')
	{
		*result = ft_str_char_join(*result, '\\');
		*result = ft_str_char_join(*result, envp[idx++]);
	}
	else
		*result = ft_str_char_join(*result, envp[idx++]);
	return (idx);
}

int		chk_bslash_print_export(int *flag, char *envp, int idx, char **result)
{
	if (*flag == 0)
		idx = chk_backslash_flag_zero(envp, idx, result);
	else if (*flag & D_QUOTE)
	{
		*result = ft_str_char_join(*result, envp[idx++]);
		if (envp[idx] == '\"' || envp[idx] == '\\' ||
		envp[idx] == '`' || envp[idx] == '$')
			*result = ft_str_char_join(*result, envp[idx++]);
		else
		{
			*result = ft_str_char_join(*result, '\\');
			*result = ft_str_char_join(*result, envp[idx++]);
		}
	}
	else if (*flag & S_QUOTE)
	{
		*result = ft_str_char_join(*result, '\\');
		*result = ft_str_char_join(*result, envp[idx++]);
	}
	return (idx);
}

int		chk_other_cases_print(int *flag, char *envp, int idx, char **result)
{
	if (envp[idx] == '\\')
		idx = chk_bslash_print_export(flag, envp, idx, result);
	else
	{
		if (*flag & S_QUOTE)
		{
			if (envp[idx] == '\"' || envp[idx] == '`' || envp[idx] == '$')
				*result = ft_str_char_join(*result, '\\');
		}
		*result = ft_str_char_join(*result, envp[idx++]);
	}
	return (idx);
}

void	print_export_value(char *envp, int idx, int fd)
{
	int		flag;
	char	*result;

	flag = 0;
	result = NULL;
	if (!envp[idx])
		result = ft_strdup("");
	else if (envp[idx] == '=')
	{
		result = ft_str_char_join(result, envp[idx++]);
		result = ft_str_char_join(result, '\"');
		while (envp[idx])
		{
			if (envp[idx] == '\"' && !(flag & S_QUOTE))
				idx = turn_on_flag(&flag, D_QUOTE, idx);
			else if (envp[idx] == '\'' && !(flag & D_QUOTE))
				idx = turn_on_flag(&flag, S_QUOTE, idx);
			else
				idx = chk_other_cases_print(&flag, envp, idx, &result);
		}
		result = ft_str_char_join(result, '\"');
	}
	ft_putstr_fd(result, fd);
	free_str(result);
	free_str(envp);
}
