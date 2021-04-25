#include "minishell.h"

void	minishell(char *argv, char **envp)
{
	int 	status;
	char	*input_string;
	char	**cmd_set;
	t_cmd	*list;

	int		i;

	status = 1;
	while (status)
	{
		write(1, "> ", 2);
		read_cmd(&input_string);
		if (!check_syntax_err(input_string))
			continue ;
		cmd_set = separate(input_string, ';');
		i = 0;
		while (cmd_set && cmd_set[i])
		{
			list = get_parsed_list(cmd_set[i++]);
			// if (!list)
			run(list);
		}
		i = 0;
		while (cmd_set && cmd_set[i])
			free(cmd_set[i++]);
		if (cmd_set != NULL)
			free(cmd_set);

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

			// while (list->next)
			// {
			// 	while (list->token->next)
			// 	{
			// 		printf("%d : %s\n", list->token->type, list->token->arg);
			// 		list->token = list->token->next;
			// 	}
			// 	printf("%d : %s\n", list->token->type, list->token->arg);
			// 	list = list->next;
			// }
			// while (list->token->next)
			// {
			// 	printf("%d : %s\n", list->token->type, list->token->arg);
			// 	list->token = list->token->next;
			// }
			// printf("%d : %s\n", list->token->type, list->token->arg);