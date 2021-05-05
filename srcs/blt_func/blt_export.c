#include "minishell.h"

char	*set_export_value(char *envp, int idx)
{
	int		is_dquote;
	int		is_squote;
	char	*result;

	result = NULL;
	is_dquote = 0;
	is_squote = 0;
	if (!envp[idx])
		result = ft_strdup("");
	else if (envp[idx++] == '=')
	{
		
	}
	return (result);
}

int		set_env_name(char **export_name)
{
	int		i;
	char	*result;

	i = -1;
	result = NULL;
	while (*export_name[++i] || *export_name[i] != '$')
	{
		if (ft_isalpha(*export_name[i]))
			result = ft_str_char_join(result, *export_name[i]);
		else if (ft_isdigit(*export_name[i]))
		{
			if (i > 0 && (*export_name[i] != '\'' || *export_name[i] != '\"'))
				result = ft_str_char_join(result, *export_name[i]);
		}
		else if (*export_name[i] == '\"')
		{
			if (*export_name[i + 1] == '$')
				;
		}
	}
}

void	print_export(char **envp)
{
	int		i;
	int		j;
	char	**export;
	char	*export_name;
	char	*tmp;

	i = 0;
	while (envp[i])
		i++;
	export = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		export[i] = ft_strdup(envp[i]);
	export[i] = NULL;
	i--;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(export[j], export[j + 1]) > 0)
			{
				tmp = export[j + 1];
				export[j + 1] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i--;
	}
	i = -1;
	while (export[++i])
	{
		j = 0;
		export_name = NULL;
		while (export[i][j] && export[i][j] != '=')
			export_name = ft_str_char_join(export_name, export[i][j++]);
		tmp = set_export_value(export[i], j);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(export_name, STDOUT_FILENO);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(export_name);
		free(tmp);
		// free(export[i]);
	}
	// free(export);
}

int		blt_export(t_token *token, char ***envp)
{
	int		i;
	int		idx;
	char	*export_name;

	if (!token->next)
		print_export(*envp);
	else
	{
		export_name = NULL;
		while (token)
		{
			if (token->type == ARGUMENT)
			{
				// if (token->arg[0] == '=')
				// 	; // error;
				// else
				// {
				// 	i = 0;
				// 	while (token->arg[i] || token->arg[i] != '=')
				// 		export_name = ft_str_char_join(export_name, token->arg[i++]);
				// 	if (!set_env_name(&export_name))
				// 		; // error
					idx = find_env_name(export_name, *envp);
					if (idx > 0)
						// ;// duplicate envp[idx]
						ft_strlcpy(*envp[idx], token->arg, ft_strlen(token->arg) + 1);
					else
						// ;// *envp
						*envp = add_env(*envp, token->arg);
				// }
			}
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
	return (1);
}
