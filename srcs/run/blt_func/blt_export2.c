/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:43 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 17:59:44 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		chk_export_var(char *name, char **result, char **envp, int i)
{
	char	*key;

	key = NULL;
	while (!ft_strchr(" \t\n$\"\'\\=", name[++i]))
		key = ft_str_char_join(key, name[i]);
	if (find_env_name(key, envp) >= 0)
		*result = ft_strjoin(*result,
		set_export_value(find_env_value(key, envp), 0, envp), 1);
	free_str(key);
	return (i);
}

int		set_env_name(char **name, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if ((*name)[0] != '$' && (*name)[0] != '_' && ft_isalpha((*name)[0]) == 0)
		return (0);
	while ((*name)[i])
	{
		if ((*name)[i] == '$')
			i = chk_export_var(*name, &result, envp, i);
		else
			result = ft_str_char_join(result, (*name)[i++]);
	}
	free(*name);
	*name = result;
	if (!(*name) || ft_isdigit((*name)[0]))
		return (0);
	i = -1;
	while ((*name)[++i])
	{
		if ((*name)[i] != '_' && ft_isalpha((*name)[i]) == 0)
			return (0);
	}
	return (1);
}

/*	*/

void	sort_export(char ***export, int i)
{
	int		j;
	char	*tmp;

	i--;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp((*export)[j], (*export)[j + 1]) > 0)
			{
				tmp = (*export)[j + 1];
				(*export)[j + 1] = (*export)[j];
				(*export)[j] = tmp;
			}
			j++;
		}
		i--;
	}
}

void	set_print_export(char *export)
{
	int		j;
	char	*export_name;

	j = 0;
	export_name = NULL;
	while (export[j] && export[j] != '=')
		export_name = ft_str_char_join(export_name, export[j++]);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(export_name, STDOUT_FILENO);
	print_export_value(export, j, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free_str(export_name);
}

void	print_export(char **envp)
{
	int		i;
	char	**export;

	i = 0;
	while (envp[i])
		i++;
	export = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		export[i] = ft_strdup(envp[i]);
	export[i] = NULL;
	sort_export(&export, i);
	i = -1;
	while (export[++i])
		set_print_export(export[i]);
	free(export);
}
