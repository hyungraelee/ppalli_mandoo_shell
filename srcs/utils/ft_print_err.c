#include "minishell.h"

int	ft_print_err(char *s1, char *s2, char *s3, int code)
{
	char	*print;

	g_exit = code;
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
