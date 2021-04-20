#include "read_cmd.h"

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

int	read_cmd(char **line)
{
	int	c;

	*line = NULL;
	while (read(0, &c, sizeof(c)) > 0)
	{
		*line = ft_str_char_join(*line, c);
		if (c == '\n')
			break;
		c = 0;
	}
	return (1);
}

// int	read_cmd(char **line)
// {
// 	struct termios	term;
// 	char			c;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ICANON;    // non-canonical input 설정
// 	term.c_lflag &= ECHO;      // 입력 시 터미널에 보이도록
// 	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
// 	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	*line = NULL;
// 	while (read(0, &c, sizeof(c)) > 0 && c != '\n')
// 		*line = ft_str_char_join(*line, c);
// 	return (1);
// }



// int	main()
// {
// 	struct termios term;
// 	char c;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~(ICANON|~ECHO);    // non-canonical input 설정
// 	// term.c_lflag &= ~ICANON;    // non-canonical input 설정
// 	// term.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
// 	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
// 	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);

// 	int i = 0;
// 	while (read(0, &c, sizeof(c)) > 0 && c != '\n')
// 	{
// 		i++;
// 		// printf("%c\n", c);
// 	}
// }
