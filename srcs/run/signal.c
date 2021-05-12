#include "minishell.h"

void	sig_handler(int signo)
{
	if (g_global.pid > 0)
	{
		if (!kill(g_global.pid, signo))
		{
			g_global.signal_on = 1;
			if (signo == SIGINT)
				ft_putstr_fd("\n", STDOUT_FILENO);
			else if (signo == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		}
		else
		{
			if (signo == SIGINT)
			{
				ft_putstr_fd("\n", STDOUT_FILENO);
				g_global.signal_on = 1;
				g_global.exit = 1;
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
