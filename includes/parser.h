#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

# define KEY_BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define KEY_ENTER 10
# define KEY_TAB 9
# define QUERY_CURSOR_POSITION "\033[6n"

char	*read_cmd(t_history **last);
int		check_syntax_err(char *line);
char	**separate(char *line, char c);
char	*ft_strcpy_i_to_j(char *line, int i, int j);
t_cmd	*get_parsed_list(char *line);
t_token	*make_tokenlist(char *cmdline, char **cmd_name);
void	delete_letter(void);
void	move_cursor_left(void);
void	move_cursor_right(void);
void	delete_current_line(void);
void	prompt(void);

#endif
