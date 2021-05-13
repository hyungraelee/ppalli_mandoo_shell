#include "minishell.h"

static void	init_read_cmd(t_read *read_cmd, t_history **last)
{
	read_cmd->result = NULL;
	read_cmd->new = ft_strdup("");
	read_cmd->on_terminal = &(read_cmd->new);
	read_cmd->cursor = 0;
	read_cmd->selected_history = *last;
	read_cmd->c = 0;
}

static void	handle_signal_in_read(t_read *read_cmd)
{
	if (*(read_cmd->on_terminal) != read_cmd->new)
	{
		free(read_cmd->selected_history->edit_record);
		read_cmd->selected_history->edit_record = ft_strdup(read_cmd->selected_history->record);
	}
	free(read_cmd->new);
	read_cmd->new = ft_strdup("");
	read_cmd->on_terminal = &(read_cmd->new);
	read_cmd->cursor = 0;
	g_global.signal_on = 0;
}

static int	is_key_arrow(int c)
{
	return (c == UP_ARROW || c == DOWN_ARROW || c == RIGHT_ARROW || c == LEFT_ARROW);
}

static int	is_special_key(int c)
{
	return (c == KEY_BACKSPACE || c == KEY_HOME || c == KEY_END || c == KEY_CTRL_D || c == KEY_TAB);
}

char	*read_cmd(t_history **last)
{
	t_read	read_cmd;

	init_read_cmd(&read_cmd, last);
	while (read(0, &(read_cmd.c), sizeof(read_cmd.c)) > 0)
	{
		if (g_global.signal_on)
			handle_signal_in_read(&read_cmd);
		if (is_key_arrow(read_cmd.c))
			handle_key_arrow(&read_cmd, last);
		else if (is_special_key(read_cmd.c))
			handle_special_key(&read_cmd, last);
		else if (read_cmd.c == KEY_ENTER)
		{
			handle_key_enter(&read_cmd, last);
			break;
		}
		else
			handle_normal_key(&read_cmd);
		read_cmd.c = 0;
	}
	if (read_cmd.new)
		free(read_cmd.new);
	read_cmd.new = NULL;
	return (read_cmd.result);
}
