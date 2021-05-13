#include "minishell.h"

void		free_history(t_history *history)
{
	while (history)
	{
		free(history->record);
		free(history->edit_record);
		if (history->prev)
			history = history->prev;
		else
			break ;
	}
}

static void	handle_key_backspace(t_read *read_cmd)
{
	if (read_cmd->cursor > 0)
	{
		delete_letter();
		*(read_cmd->on_terminal) = \
		ft_str_char_del(*(read_cmd->on_terminal), read_cmd->cursor - 1);
		(read_cmd->cursor)--;
	}
}

static void	handle_key_home_end(t_read *read_cmd)
{
	if (read_cmd->c == KEY_HOME)
	{
		while (read_cmd->cursor > 0)
		{
			move_cursor_left();
			(read_cmd->cursor)--;
		}
	}
	else if (read_cmd->c == KEY_END)
	{
		while (read_cmd->cursor < ft_strlen(*(read_cmd->on_terminal)))
		{
			move_cursor_right();
			(read_cmd->cursor)++;
		}
	}
}

static void	handle_key_ctrl_d(t_read *read_cmd, t_history **last)
{
	if (!ft_strcmp(*(read_cmd->on_terminal), ""))
	{
		free_history(*last);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
}

void		handle_special_key(t_read *read_cmd, t_history **last)
{
	if (read_cmd->c == KEY_BACKSPACE)
		handle_key_backspace(read_cmd);
	else if (read_cmd->c == KEY_HOME || read_cmd->c == KEY_END)
		handle_key_home_end(read_cmd);
	else if (read_cmd->c == KEY_CTRL_D)
		handle_key_ctrl_d(read_cmd, last);
	else if (read_cmd->c == KEY_TAB)
		;
}
