#include "minishell.h"

static t_history	*history_init(void)
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

void				handle_key_enter(t_read *read_cmd, t_history **last)
{
	write(1, &(read_cmd->c), 1);
	if (ft_strcmp(*(read_cmd->on_terminal), ""))
	{
		read_cmd->temp = history_init();
		read_cmd->temp->record = ft_strdup(*(read_cmd->on_terminal));
		read_cmd->temp->edit_record = ft_strdup(read_cmd->temp->record);
		if (!(*last))
		{
			*last = read_cmd->temp;
			read_cmd->selected_history = (*last);
		}
		else
		{
			(*last)->next = read_cmd->temp;
			read_cmd->temp->prev = (*last);
			(*last) = (*last)->next;
		}
	}
	read_cmd->result = ft_strdup(*(read_cmd->on_terminal));
	if (*(read_cmd->on_terminal) != read_cmd->new)
	{
		free(read_cmd->selected_history->edit_record);
		read_cmd->selected_history->edit_record = \
		ft_strdup(read_cmd->selected_history->record);
	}
}

void				handle_normal_key(t_read *read_cmd)
{
	*(read_cmd->on_terminal) = \
	ft_str_char_embed(*(read_cmd->on_terminal), read_cmd->c, read_cmd->cursor);
	read_cmd->cursor++;
	read_cmd->c = read_cmd->cursor;
	while (read_cmd->c != ft_strlen(*(read_cmd->on_terminal)))
	{
		move_cursor_right();
		(read_cmd->c)++;
	}
	while (--(read_cmd->c) > 0)
		delete_letter();
	ft_putstr_fd(*(read_cmd->on_terminal), 1);
	read_cmd->c = ft_strlen(*(read_cmd->on_terminal));
	while ((read_cmd->c)-- > read_cmd->cursor)
		move_cursor_left();
}
