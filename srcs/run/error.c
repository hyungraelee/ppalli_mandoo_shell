#include "minishell.h"

int	ft_print_err(char *s1, char *s2, char *s3, int code)
{
	char	*print;

	g_global.exit = code;
	print = ft_strdup("minishell: ");
	print = ft_strjoin(print, s1, 1);
	print = ft_strjoin(print, ": ", 1);
	print = ft_strjoin(print, s2, 1);
	if (s3)
	{
		print = ft_strjoin(print, ": ", 1);
		print = ft_strjoin(print, s3, 1);
	}
	print = ft_strjoin(print, "\n", 1);
	ft_putstr_fd(print, STDERR_FILENO);
	free(print);
	return (0);
}

int	ft_print_synerr(char c, int rd)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	if (rd == 3)
		write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	g_global.exit = 258;
	return (0);
}
