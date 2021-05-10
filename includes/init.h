#ifndef INIT_H
# define INIT_H

# include "minishell.h"

char	**init_envp(char **env);
void	init_termios(void);
void	init_termcap(void);

#endif
