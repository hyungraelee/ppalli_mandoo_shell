#include "minishell.h"

char	*read_line()
{
	char	*line;

	get_next_line(0, &line);
	return (line);
}

void	minishell(char *argv, char **envp)
{
	int status;
	char	*cmd;

	status = 1;
	while (status)
	{
		write(1, "> ", 2);
		cmd = read_line();
		printf("%s\n", cmd);
	}
}

int main(int argc, char **argv, char **envp)
{
	minishell(argv[0], envp);

}
