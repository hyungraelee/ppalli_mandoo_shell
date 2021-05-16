/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:14 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:00:15 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_set_envp(char *env_temp, char *result)
{
	int	j;

	j = 0;
	while (env_temp && env_temp[j])
	{
		if (env_temp[j] == ' ' || env_temp[j] == '\t' || env_temp[j] == '\n')
		{
			result = ft_str_char_join(result, ' ');
			while (env_temp[j] == ' ' ||
			env_temp[j] == '\t' || env_temp[j] == '\n')
				j++;
		}
		else
		{
			result = ft_str_char_join(result, env_temp[j]);
			j++;
		}
	}
	return (result);
}

int		get_env_other_cases(char *arg, char **envp, char **result, int i)
{
	char	*env_name;
	char	*env_temp;

	if (arg[i] == '$')
	{
		if (arg[i + 1] == '?')
		{
			*result = ft_strjoin(*result, ft_itoa(g_global.exit), 3);
			i += 2;
		}
		else
		{
			env_name = NULL;
			env_temp = NULL;
			while (!ft_strchr(" \t\n$\"\'\\", arg[++i]))
				env_name = ft_str_char_join(env_name, arg[i]);
			env_temp = set_env_value(find_env_value(env_name, envp), 0);
			*result = get_env_set_envp(env_temp, *result);
			free_str(env_name);
			free_str(env_temp);
		}
	}
	else
		*result = ft_str_char_join(*result, arg[i++]);
	return (i);
}

int		get_env_dquote_envp(char *arg, char **envp, char **result, int i)
{
	char	*env_name;
	char	*env_temp;

	env_name = NULL;
	env_temp = NULL;
	if (arg[i + 1] == '?')
	{
		*result = ft_strjoin(*result, ft_itoa(g_global.exit), 3);
		i += 2;
	}
	else
	{
		while (!ft_strchr(" \t\n$\"\'\\", arg[++i]))
			env_name = ft_str_char_join(env_name, arg[i]);
		env_temp = set_env_value(find_env_value(env_name, envp), 0);
		*result = ft_strjoin(*result, env_temp, 1);
	}
	free_str(env_name);
	free_str(env_temp);
	return (i);
}

int		get_env_dquote(char *arg, char **envp, char **result, int i)
{
	i++;
	while (arg[i] != '\"')
	{
		if (arg[i] == '\\')
		{
			if (arg[i + 1] == '\"' || arg[i + 1] == '\\' || arg[i + 1] == '`' || arg[i + 1] == '$')
				*result = ft_str_char_join(*result, arg[++i]);
			else
				*result = ft_str_char_join(*result, arg[i]);
			i++;
		}
		else if (arg[i] == '$')
			i = get_env_dquote_envp(arg, envp, result, i);
		else
			*result = ft_str_char_join(*result, arg[i++]);
	}
	i++;
	return (i);
}

char	*get_env_value(char *arg, char **envp)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'')
				result = ft_str_char_join(result, arg[i++]);
			i++;
		}
		else if (arg[i] == '\"')
			i = get_env_dquote(arg, envp, &result, i);
		else
			i = get_env_other_cases(arg, envp, &result, i);
	}
	free(arg);
	return (result);
}
