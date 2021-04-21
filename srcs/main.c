#include "minishell.h"

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
		read_cmd(&cmdlines);
		cmds = sep_cmdline(cmdlines , ';');
		free(cmdlines);
		i = 0;
		while (cmds && cmds[i])
		{
			// write(1, cmds[i], ft_strlen(cmds[i]));
			printf("%s\n", cmds[i]);
			i++;
		}
		i = 0;
		while (cmds && cmds[i])
			free(cmds[i++]);
		if (cmds != NULL)
			free(cmds);

	}
}

void	init_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag |= ECHO;		// 입력시 터미널에 보이도록
	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int		main(int argc, char **argv, char **envp)
{
	init_termios();
	minishell(argv[0], envp);
}
