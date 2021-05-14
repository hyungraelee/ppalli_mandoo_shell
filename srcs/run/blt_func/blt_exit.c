#include "minishell.h"

static void	handle_exit_arg(t_token *token, int *exit_code)
{
	int	i;

	i = 0;
	if (token->arg[i] == '-')
		i++;
	while (token->arg[i])
	{
		if (!ft_isdigit(token->arg[i++]))
		{
			ft_print_err("exit", token->arg, ERR_MSG6, 255);
			exit(255);
		}
	}
	*exit_code = ft_atoi(token->arg);
}

int			blt_exit(t_token *token, char ***envp)
{
	int	cnt;
	int	exit_code;

	write(STDERR_FILENO, "exit\n", 5);
	cnt = 0;
	exit_code = 0;
	while (token)
	{
		if (token->type == ARGUMENT)
		{
			cnt++;
			if (cnt == 2)
				return (ft_print_err("exit", ERR_MSG7, NULL, 1));
			handle_exit_arg(token, &exit_code);
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	g_global.exit = exit_code;
	exit(exit_code);
}
