#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	**envp;

	envp = init(env);
	minishell(envp);
	system("leaks minishell");
}
