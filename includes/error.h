#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define ERR_MSG1 "not a valid identifier"
# define ERR_MSG2 "is a directory"
# define ERR_MSG3 "Permission denied"
# define ERR_MSG4 "HOME not set"
# define ERR_MSG5 "OLDPWD not set"
# define ERR_MSG6 "numeric argument required"
# define ERR_MSG7 "too many arguments"
# define ERR_MSG8 "No such file or directory"
# define ERR_MSG9 "command not found"

int	ft_print_err(char *s1, char *s2, char *s3, int code);
int	ft_print_synerr(char c, int rd);

#endif
