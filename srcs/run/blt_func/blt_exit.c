#include "minishell.h"

int		blt_exit(t_token *token, char ***envp)
{
	int	cnt;
	int	i;
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
			{
				ft_print_err("exit", "too many arguments", NULL, 1);
				g_global.exit = 1;
				return (0);
			}
			i = 0;
			if (token->arg[i] == '-')
				i++;
			while (token->arg[i])
			{
				if (!ft_isdigit(token->arg[i++]))
				{
					ft_print_err("exit", token->arg, "numeric argument required", 255);
					g_global.exit = 255;
					exit(255);
				}
			}
			exit_code = ft_atoi(token->arg);
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	g_global.exit = exit_code;
	exit(exit_code);
}
