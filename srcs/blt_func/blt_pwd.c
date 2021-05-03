#include "minishell.h"

int	blt_pwd(t_token *token, char **envp)
{
	char	*pwd;
	int		trash;

	trash = token->type;
	pwd = ft_strjoin(ft_strdup(find_env_value("PWD", envp)), "\n", 1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	return (1);
}
