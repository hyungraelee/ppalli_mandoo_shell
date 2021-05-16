/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_setting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:14 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:08:39 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_SETTING_H
# define PRE_SETTING_H

# include "structures.h"

# define KEY_BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define KEY_ENTER 10
# define KEY_TAB 9
# define KEY_HOME 4741915
# define KEY_END 4610843
# define KEY_CTRL_D 4

char	*read_cmd(t_history **last);
void	handle_key_arrow(t_read *read_cmd, t_history **last);
void	handle_special_key(t_read *read_cmd, t_history **last);
void	handle_normal_key(t_read *read_cmd);
void	handle_key_enter(t_read *read_cmd, t_history **last);
void	free_history(t_history *history);

int		check_syntax(char *line);
int		handle_special_letter(char *input_string, int *i, char *sflag, int *rd);

char	**separate(char *line, char c);

t_cmd	*get_parsed_list(char *line);

t_token	*get_token_list(char *cmdline, char **cmd_name);
t_token	*make_token_list(char **args, char **cmd_name);
char	**token_array(char **args, char *cmdline);

void	delete_letter(void);
void	move_cursor_left(void);
void	move_cursor_right(void);
void	delete_current_line(void);

void	prompt(void);

#endif
