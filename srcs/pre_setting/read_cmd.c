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
			break;
	}
}

t_history	*history_init(void)
{
	t_history	*result;

	result = (t_history *)malloc(sizeof(t_history));
	if (!result)
		return (NULL);
	result->record = NULL;
	result->edit_record = NULL;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

char	*read_cmd(t_history **last)
{
	char		*result;
	char		**on_terminal;
	int			c;
	int			cursor;
	char		*new;
	t_history	*temp;
	t_history	*selected_history;

	result = NULL;
	new = ft_strdup("");
	on_terminal = &new;
	cursor = 0;
	selected_history = *last;
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (g_global.signal_on)
		{
			if (*on_terminal != new)
			{
				free(selected_history->edit_record);
				selected_history->edit_record = ft_strdup(selected_history->record);
			}
			free(new);
			new = ft_strdup("");
			on_terminal = &new;
			cursor = 0;
			g_global.signal_on = 0;
		}
		if (c == KEY_BACKSPACE)
		{
			if (cursor > 0)
			{
				delete_letter();
				*on_terminal = ft_str_char_del(*on_terminal, cursor - 1);
				cursor--;
			}
		}
		else if (c == UP_ARROW)
		{
			if (*on_terminal == new)
			{
				if (*last)
				{
					selected_history = *last;
					on_terminal = &selected_history->edit_record;
				}
			}
			else
			{
				if (selected_history->prev)
				{
					selected_history = selected_history->prev;
					on_terminal = &selected_history->edit_record;
				}
			}
			cursor = ft_strlen(*on_terminal);
			delete_current_line();
			prompt();
			ft_putstr_fd(*on_terminal, 1);
		}
		else if (c == DOWN_ARROW)
		{
			if (*on_terminal != new)
			{
				if (selected_history->next)
				{
					selected_history = selected_history->next;
					on_terminal = &selected_history->edit_record;
				}
				else
					on_terminal = &new;
			}
			cursor = ft_strlen(*on_terminal);
			delete_current_line();
			prompt();
			ft_putstr_fd(*on_terminal, 1);
		}
		else if (c == LEFT_ARROW)
		{
			if (cursor > 0)
			{
				move_cursor_left();
				cursor--;
			}
		}
		else if (c == RIGHT_ARROW)
		{
			if (cursor < ft_strlen(*on_terminal))
			{
				move_cursor_right();
				cursor++;
			}
		}
		else if (c == KEY_HOME)
		{
			while (cursor > 0)
			{
				move_cursor_left();
				cursor--;
			}
		}
		else if (c == KEY_END)
		{
			while (cursor < ft_strlen(*on_terminal))
			{
				move_cursor_right();
				cursor++;
			}
		}
		else if (c == KEY_CTRL_D)
		{
			if (!ft_strcmp(*on_terminal, ""))
			{
				free_history(*last);
				ft_putstr_fd("exit\n", STDOUT_FILENO);
				exit (0);
			}
		}
		else if (c == KEY_ENTER)
		{
			write(1, &c, 1);
			if (ft_strcmp(*on_terminal, ""))
			{
				temp = history_init();
				temp->record = ft_strdup(*on_terminal);
				temp->edit_record = ft_strdup(temp->record);
				if (!(*last))
				{
					*last = temp;
					selected_history = (*last);
				}
				else
				{
					(*last)->next = temp;
					temp->prev = (*last);
					(*last) = (*last)->next;
				}
			}
			result = ft_strdup(*on_terminal);
			if (*on_terminal != new)
			{
				free(selected_history->edit_record);
				selected_history->edit_record = ft_strdup(selected_history->record);
			}
			break;
		}
		else if (c == KEY_TAB)
			;
		else
		{
			write(1, &c, 1);
			*on_terminal = ft_str_char_embed(*on_terminal, c, cursor);
			delete_current_line();
			prompt();
			ft_putstr_fd(*on_terminal, 1);
			c = ft_strlen(*on_terminal);
			cursor++;
			while (c-- > cursor)
				move_cursor_left();
		}
		c = 0;
	}
	if (new)
		free(new);
	new = NULL;
	return (result);
}
