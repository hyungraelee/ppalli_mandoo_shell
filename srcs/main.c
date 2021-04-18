#include "minishell.h"

char	*read_line()
{
	char	*line;

	get_next_line(0, &line);
	return (line);
}

void	minishell(char *argv, char **envp)
{
	int 	status;
	char	*cmdlines;

	status = 1;
	while (status)
	{
		write(1, "> ", 2);
		cmdlines = read_line();
	}
}

int		main(int argc, char **argv, char **envp)
{
	minishell(argv[0], envp);

}
