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
	char	**cmds;

	int		i;

	status = 1;
	while (status)
	{
		write(1, "> ", 2);
		cmdlines = read_line();
		cmds = sep_cmdline(cmdlines);
		i = 0;
		while (cmds[i])
			printf("%s\n", cmds[i++]);
	}
}

int		main(int argc, char **argv, char **envp)
{
	minishell(argv[0], envp);

}
