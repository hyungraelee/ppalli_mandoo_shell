#include "minishell.h"

static void	run_minishell(t_minishell *minishell, char ***envp)
{
	int	i;

	i = 0;
	while (minishell->cmd_set && (minishell->cmd_set)[i])
	{
		minishell->cmd_list = get_parsed_list((minishell->cmd_set)[i++]);
		run(minishell->cmd_list, envp);
		free_cmdlist(minishell->cmd_list);
	}
}

void		minishell(char **envp)
{
	t_minishell	shell;

	shell.last = NULL;
	g_global.pid = 1;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		prompt();
		init_termios(&(shell.backup));
		shell.input_str = read_cmd(&(shell.last));
		tcsetattr(STDIN_FILENO, TCSANOW, &(shell.backup));
		if (!ft_strcmp(shell.input_str, "") || !check_syntax(shell.input_str))
		{
			free(shell.input_str);
			shell.input_str = NULL;
			continue ;
		}
		shell.cmd_set = separate(shell.input_str, ';');
		run_minishell(&shell, &envp);
		free_minishell(&shell);
	}
}
