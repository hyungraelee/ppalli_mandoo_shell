#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define ERR_MSG1 "not a valid identifier"

int	ft_print_err(char *s1, char *s2, char *s3, int code);
int	ft_print_synerr(char c, int rd);

#endif
