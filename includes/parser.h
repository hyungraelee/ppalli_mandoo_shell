#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

# define NONE 0
# define CMD 1
# define REDIRECT 2
# define PIPE 4
# define ARG 8
# define POSSIBLE 16 // file exist after redirect
# define S_QUOTE 32
# define D_QUOTE 64

int		read_cmd(char **line);
int		check_syntax_err(char *line);
t_cmd	*get_parsed_list(char *line);

#endif
