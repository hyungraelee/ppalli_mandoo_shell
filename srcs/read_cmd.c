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
	int			col;
	char		*new;
	t_history	*temp;
	t_history	*now;

	result = NULL;
	new = ft_strdup("");
	current = &new;
	col = 0;
	now = *last;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == KEY_BACKSPACE)
		{
			if (col-- > 0)
			{
				delete_letter();
				*current = ft_str_char_del(*current);
			}
			if (col < 0)
				col = 0;
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
			col = ft_strlen(*current);
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
			col = ft_strlen(*current);
			delete_current_line();
			prompt();
			ft_putstr_fd(*current, 1);
		}
		else if (c == KEY_ENTER)
		{
			write(1, &c, 1);
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
			result = ft_strdup(*current);
			if (*current != new)
			{
				free(now->edit_record);
				now->edit_record = ft_strdup(now->record);
			}
			break;
		}
		else
		{
			write(1, &c, 1);
			col++;
			*current = ft_str_char_join(*current, c);
		}
		c = 0;
	}
	if (new)
		free(new);
	new = NULL;
	return (result);
}
