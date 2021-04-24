#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int		read_cmd(char **line);
int		check_syntax_err(char *line);
t_cmd	*get_parsed_list(char *line);

#endif
