#include "minishell.h"

void	prompt(void)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (g_global.exit == 0)
		write(1, B_GREEN, ft_strlen(B_GREEN));
	else
		write(1, B_RED, ft_strlen(B_RED));
	write(1, buf, ft_strlen(buf));
	write(1, " > ", 3);
	write(1, C_RESET, ft_strlen(C_RESET));
}

int		main(int argc, char **argv, char **env)
{
	char	**envp;

	init_termios();
	init_termcap();
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
