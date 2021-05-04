#include "minishell.h"

void	print_export(char **envp)
{
	int		i;
	int		j;
	char	**export;
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
		j = 1;
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(export[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(export[i]);
	}
	free(export);
}

int		blt_export(t_token *token, char ***envp)
{
	int		i;
	char	*export_name;

	if (!token->next)
		print_export(*envp);
	else
	{
		while (token)
		{
			if (token->type == ARGUMENT)
			{
				if (token->arg[0] == '=')
					; // error;
				else
				{
					// i = 0;
					// while (token->arg[i] == '=' && token->arg[i])
					// if (!find_env_value())
					*envp = add_env(*envp, token->arg);
				}
			}
			if (token->next)
				token = token->next;
			else
				break ;
		}
	}
	return (1);
}
