#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	**envp;

	init_termios();
	init_termcap();
	envp = init_envp(env);
	minishell(envp);
}
