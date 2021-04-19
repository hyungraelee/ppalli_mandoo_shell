#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <get_next_line_bonus.h>
# include <structures.h>

# define OFF 0
# define ON 1

char	**sep_cmdline(char *line);

#endif
