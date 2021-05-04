#include "minishell.h"

void	minishell(char **envp)
{
	int 	status;
	char	*input_string;
	char	**cmd_set;
	t_cmd	*cmd_list;
	pid_t	pid;
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
			cmd_list = get_parsed_list(cmd_set[i++]);
			// if (!list)
			status = run(cmd_list, &envp);
		}
		free(input_string);
		i = 0;
		while (cmd_set && cmd_set[i])
			free(cmd_set[i++]);
		if (cmd_set != NULL)
			free(cmd_set);

	}
}

char	**init_envp(char **env)
{
	int		i;
	int		j;
	char	**envp;

	i = -1;
	while (env[++i])
		;
	envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
	{
		envp[i] = (char *)ft_calloc(PATH_MAX + 1, sizeof(char));
		j = -1;
		while (env[i][++j])
			envp[i][j] = env[i][j];
		envp[i][j] = 0;
	}
	envp[i] = NULL;
	return (envp);
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

int		main(int argc, char **argv, char **env)
{
	char	**envp;

	init_termios();
	envp = init_envp(env);
	minishell(envp);
}

			// while (cmd_list->next)
			// {
			// 	printf("cmd_name = %s\n", cmd_list->cmd_name);
			// 	while (cmd_list->token->next)
			// 	{
			// 		printf("1 %d : %s\n", cmd_list->token->type, cmd_list->token->arg);
			// 		cmd_list->token = cmd_list->token->next;
			// 	}
			// 	printf("2 %d : %s\n", cmd_list->token->type, cmd_list->token->arg);
			// 	cmd_list = cmd_list->next;
			// }
			// while (cmd_list->token->next)
			// {
			// 	printf("cmd_name = %s\n", cmd_list->cmd_name);
			// 	printf("3 %d : %s\n", cmd_list->token->type, cmd_list->token->arg);
			// 	cmd_list->token = cmd_list->token->next;
			// }
			// printf("4 %d : %s\n", cmd_list->token->type, cmd_list->token->arg);
