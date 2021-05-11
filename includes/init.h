#ifndef INIT_H
# define INIT_H

# include <termios.h>
# include "minishell.h"

char	**init(char **env);
void	init_termios(struct termios *backup);

#endif
