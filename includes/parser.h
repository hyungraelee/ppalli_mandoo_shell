#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int		read_cmd(char **line);
int		check_syntax_err(char *line);
char	**separate(char *line, char c);
char	*ft_strcpy_i_to_j(char *line, int i, int j);
t_cmd	*get_parsed_list(char *line);
t_token	*make_tokenlist(char *cmdline, char **cmd_name);

#endif
