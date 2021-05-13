#include "minishell.h"

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
	if (export_name)
		free(export_name);
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
}

int		handle_normal_export(char ***envp, char *arg, char *name, char *value)
{
	int		i;
	int		idx;
	int		is_err;
	char	*new_var;
	
	i = 0;
	while (arg[i] && arg[i] != '=')
		name = ft_str_char_join(name, arg[i++]);
	is_err = set_env_name(&name, *envp);
	if (is_err == 0)
		return (0);
	else
	{
		value = set_export_value(arg, i, *envp);
		new_var = ft_strjoin(name, value, 0);
		idx = find_env_name(name, *envp);
		if (idx >= 0)
			ft_strlcpy((*envp)[idx], new_var, ft_strlen(new_var) + 1);
		else
			*envp = add_env(*envp, new_var);
	}
	if (name)
		free(name);
	if (value)
		free(value);
	return (1);
}

int		blt_export(t_token *token, char ***envp)
{
	char	*name;
	char	*value;

	if (!token->next)
		print_export(*envp);
	else
	{
		while (token)
		{
			if (token->type == ARGUMENT)
			{
				if (token->arg[0] == '=')
					return (ft_print_err("export", ERR_MSG1, NULL, 1));
				else
				{
					name = NULL;
					if (!handle_normal_export(envp, token->arg, name, value))
						return (ft_print_err("export", ERR_MSG1, NULL, 1));
				}
			}
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
	g_global.exit = 0;
	return (1);
}
