#include "minishell.h"

static void	handle_up_arrow(t_read *read_cmd, t_history **last)
{
	if (*(read_cmd->on_terminal) == read_cmd->new)
	{
		if (*last)
		{
			read_cmd->selected_history = *last;
			read_cmd->on_terminal = &(read_cmd->selected_history->edit_record);
		}
	}
	else
	{
		if (read_cmd->selected_history->prev)
		{
			read_cmd->selected_history = read_cmd->selected_history->prev;
			read_cmd->on_terminal = &(read_cmd->selected_history->edit_record);
		}
	}
	read_cmd->cursor = ft_strlen(*(read_cmd->on_terminal));
	delete_current_line();
	prompt();
	ft_putstr_fd(*(read_cmd->on_terminal), 1);
}

static void	handle_down_arrow(t_read *read_cmd)
{
	if (*(read_cmd->on_terminal) != read_cmd->new)
	{
		if (read_cmd->selected_history->next)
		{
			read_cmd->selected_history = read_cmd->selected_history->next;
			read_cmd->on_terminal = &(read_cmd->selected_history->edit_record);
		}
		else
			read_cmd->on_terminal = &(read_cmd->new);
	}
	read_cmd->cursor = ft_strlen(*(read_cmd->on_terminal));
	delete_current_line();
	prompt();
	ft_putstr_fd(*(read_cmd->on_terminal), 1);
}

static void	handle_right_arrow(t_read *read_cmd)
{
	if (read_cmd->cursor < ft_strlen(*(read_cmd->on_terminal)))
	{
		move_cursor_right();
		(read_cmd->cursor)++;
	}
}

static void	handle_left_arrow(t_read *read_cmd)
{
	if (read_cmd->cursor > 0)
	{
		move_cursor_left();
		(read_cmd->cursor)--;
	}
}

void		handle_key_arrow(t_read *read_cmd, t_history **last)
{
	if (read_cmd->c == UP_ARROW)
		handle_up_arrow(read_cmd, last);
	else if (read_cmd->c == DOWN_ARROW)
		handle_down_arrow(read_cmd);
	else if (read_cmd->c == RIGHT_ARROW)
		handle_right_arrow(read_cmd);
	else if (read_cmd->c == LEFT_ARROW)
		handle_left_arrow(read_cmd);
}
