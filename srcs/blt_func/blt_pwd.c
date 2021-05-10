#include "minishell.h"

int	blt_pwd(t_token *token, char ***envp)
{
	char	buf[PATH_MAX];
	char	*pwd;
	int		trash;

	trash = token->type;
	if (find_env_name("PWD", *envp) > 0)
	{
		pwd = ft_strjoin(ft_strdup(find_env_value("PWD", *envp)), "\n", 1);
		ft_putstr_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		getcwd(buf, PATH_MAX);
		ft_putstr_fd(buf, STDOUT_FILENO);
	}
	g_exit = 0;
	return (1);
}
