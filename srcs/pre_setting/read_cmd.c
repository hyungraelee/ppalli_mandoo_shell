#include "minishell.h"

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
	char		**current;
	int			c;
	int			cursor;
	char		*new;
	t_history	*temp;
	t_history	*now;

	result = NULL;
	new = ft_strdup("");
	current = &new;
	cursor = 0;
	now = *last;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == KEY_BACKSPACE)
		{
			if (cursor > 0)
			{
				delete_letter();
				*current = ft_str_char_del(*current, cursor - 1);
				cursor--;
			}
		}
		else if (c == UP_ARROW)
		{
			if (*current == new)
			{
				if (*last)
				{
					now = *last;
					current = &now->edit_record;
				}
			}
			else
			{
				if (now->prev)
					now = now->prev;
				current = &now->edit_record;
			}
			cursor = ft_strlen(*current);
			delete_current_line();
			prompt();
			ft_putstr_fd(*current, 1);
		}
		else if (c == DOWN_ARROW)
		{
			if (*current != new)
			{
				if (now->next)
				{
					now = now->next;
					current = &now->edit_record;
				}
				else
					current = &new;
			}
			cursor = ft_strlen(*current);
			delete_current_line();
			prompt();
			ft_putstr_fd(*current, 1);
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
			if (cursor < ft_strlen(*current))
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
			while (cursor < ft_strlen(*current))
			{
				move_cursor_right();
				cursor++;
			}
		}
		else if (c == KEY_ENTER)
		{
			write(1, &c, 1);
			if (ft_strcmp(*current, ""))
			{
				temp = history_init();
				temp->record = ft_strdup(*current);
				temp->edit_record = ft_strdup(temp->record);
				if (!(*last))
				{
					*last = temp;
					now = (*last);
				}
				else
				{
					(*last)->next = temp;
					temp->prev = (*last);
					(*last) = (*last)->next;
				}
			}
			result = ft_strdup(*current);
			if (*current != new)
			{
				free(now->edit_record);
				now->edit_record = ft_strdup(now->record);
			}
			break;
		}
		else if (c == KEY_TAB)
			;
		else
		{
			write(1, &c, 1);
			*current = ft_str_char_embed(*current, c, cursor);
			delete_current_line();
			prompt();
			ft_putstr_fd(*current, 1);
			c = ft_strlen(*current);
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
