#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include "structures.h"
# include "read_cmd.h"
# include "utils.h"

# define OFF 0
# define ON 1

char	**sep_cmdline(char *line, char c);

#endif
