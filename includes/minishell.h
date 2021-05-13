#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <termcap.h>
# include "structures.h"
# include "pre_setting.h"
# include "run.h"
# include "utils.h"
# include "init.h"
# include "error.h"

typedef struct s_global	t_global;

struct	s_global
{
	int		exit;
	pid_t	pid;
	int		signal_on;
};

t_global	g_global;

void	minishell(char **envp);

# define B_RED "\033[1;5;31m"
# define B_GREEN "\033[1;5;92m"
# define C_RESET "\e[0m"

# define PATH_MAX 1024
# define OFF 0
# define ON 1

#endif
