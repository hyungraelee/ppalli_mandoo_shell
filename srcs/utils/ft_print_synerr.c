#include "minishell.h"

int	ft_print_synerr(char c, int rd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	if (rd == 3)
		write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	g_exit = 258;
	return (0);
}
