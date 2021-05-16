/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:59 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:04:00 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**init_envp(char **env)
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

void		init_termios(struct termios *backup)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, backup);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	init_termcap(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putstr_fd("minishell: Specify a terminal \
type with `setenv TERM <yourtype>'.", STDERR_FILENO);
		exit(1);
	}
	success = tgetent(NULL, "xterm");
	if (success < 0)
	{
		ft_putstr_fd("minishell: Could not access the \
termcap data base.", STDERR_FILENO);
		exit(1);
	}
	if (success == 0)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: \
Terminal type `", termtype, 2), "\' is not defined.", 1), STDERR_FILENO);
		exit(1);
	}
}

char		**init(char **env)
{
	char	**envp;

	init_termcap();
	envp = init_envp(env);
	return (envp);
}
