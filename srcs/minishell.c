#include "minishell.h"

void	minishell(char **envp)
{
	int 		status;
	char		*input_string;
	char		**cmd_set;
	t_cmd		*cmd_list;
	pid_t		pid;
	int			i;
	t_history	*last;

	status = 1;
	last = NULL;
	while (status)
	{
		prompt();
		input_string = read_cmd(&last);
		if (!input_string || !check_syntax_err(input_string))
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
