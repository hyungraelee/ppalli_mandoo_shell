#include "minishell.h"

void	ft_print_err(char	*s1, char *s2)
{
	char	*print;

	print = ft_strdup("minishell: ");
	print = ft_strjoin(print, s1, 1);
	print = ft_strjoin(print, ": ", 1);
	print = ft_strjoin(print, s2, 1);
	print = ft_strjoin(print, "\n", 1);
	ft_putstr_fd(print, STDERR_FILENO);
	free(print);
}

// void	ft_print_err_exit(void)
// {

// }
