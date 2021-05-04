#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "structures.h"
# include "parser.h"
# include "run.h"
# include "utils.h"


typedef int	t_exit_code;
t_exit_code	g_exit;

# define PATH_MAX 1024
# define OFF 0
# define ON 1

#endif
