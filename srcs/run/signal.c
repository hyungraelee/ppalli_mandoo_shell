#include "minishell.h"

void	sig_handler(int signo)
{
	if (g_global.pid > 0)
	{
		if (!kill(g_global.pid, signo))
		{
			if (signo == SIGINT)
			{
				ft_putstr_fd("^C\n", STDOUT_FILENO);
				// prompt();
			}
			else if (signo == SIGQUIT)
			{
				ft_putstr_fd("^\\Quit: 3\n", STDOUT_FILENO);
				// prompt();
			}
		}
		else
		{
			if (signo == SIGINT)
			{
				ft_putstr_fd("\n", STDOUT_FILENO);
				g_global.signal_on = 1;
				prompt();
			}
		}
	}
	// else if (g_global.pid == 0)
	// {
	// 	if (signo == SIGINT)
	// 	{
	// 		ft_putstr_fd("^C\n", STDOUT_FILENO);
	// 		// prompt();
	// 	}
	// 	else if (signo == SIGQUIT)
	// 	{
	// 		ft_putstr_fd("^\\Quit: 3\n", STDOUT_FILENO);
	// 		// prompt();
	// 	}
	// }
}

// int main(int argc, char **argv, char **envp)
// {
// 	int	i = 0;
// 	// char	*arg[2];

// 	// arg[0] = "cat";
// 	// arg[1] = NULL;
// 	// execve("/bin/cat", arg, envp);
// 	signal(SIGTERM, sig_handler);
// 	while (1)
// 	{
// 		printf("%d\n", i++);
// 		sleep(1);
// 	}
// }