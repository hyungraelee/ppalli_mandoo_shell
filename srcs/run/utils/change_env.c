/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:02 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:14:43 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env(char **envp, char *str)
{
	char	**result;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return (NULL);
	i = -1;
	while (envp[++i])
		result[i] = envp[i];
	result[i] = (char *)ft_calloc((PATH_MAX + 1), sizeof(char));
	ft_strlcpy(result[i], str, ft_strlen(str) + 1);
	result[++i] = NULL;
	free(str);
	free(envp);
	return (result);
}

char	**delete_env(char **envp, char *str, int idx)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * i);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != idx)
			result[j++] = envp[i++];
		else
		{
			free(envp[i]);
			i++;
		}
	}
	result[j] = NULL;
	free(envp);
	return (result);
}
