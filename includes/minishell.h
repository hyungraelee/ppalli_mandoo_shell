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

# define NONE 0
# define CMD 1
# define REDIRECT 2
# define PIPE 4
# define ARG 8
# define POSSIBLE 16 // file exist after redirect
# define S_QUOTE 32
# define D_QUOTE 64


char	**sep_cmdline(char *line, char c);

#endif
