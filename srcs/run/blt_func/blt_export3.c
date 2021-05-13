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
	if (key)
		free(key);
	return (i);
}

int		set_env_name(char **export_name, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if ((*export_name)[0] != '$' && (*export_name)[0] != '_' &&
	ft_isalpha((*export_name)[0]) == 0)
		return (0);
	while ((*export_name)[i])
	{
		if ((*export_name)[i] == '$')
			i = chk_export_var(*export_name, &result, envp, i);
		else
			result = ft_str_char_join(result, (*export_name)[i++]);
	}
	free(*export_name);
	*export_name = result;
	if (!(*export_name) || ft_isdigit((*export_name)[0]))
		return (0);
	i = -1;
	while ((*export_name)[++i])
	{
		if ((*export_name)[i] != '_' && ft_isalpha((*export_name)[i]) == 0)
			return (0);
	}
	return (1);
}
