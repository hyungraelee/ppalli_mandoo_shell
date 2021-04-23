#include "minishell.h"

t_pipe	*make_pipe(void)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->next = NULL;
	pipe->prev = NULL;
	return (pipe);
}

t_cmd	*make_cmd(char *cmdline)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	return (cmd);
}

t_cmd	*make_list(char **cmdlines)
{
	t_cmd	*list;
	t_cmd	*cmd_temp;
	t_pipe	*pipe_temp;
	int		i;

	i = 0;
	list = NULL;
	while (cmdlines[i])
	{
		cmd_temp = make_cmd(cmdlines[i]);
		if (!cmd_temp)
			return (NULL);
		if (i > 0)
		{
			pipe_temp->next = cmd_temp;
			cmd_temp->prev = pipe_temp;
		}
		if (list == NULL)
			list = cmd_temp;
		if (cmdlines[i + 1])
		{
			pipe_temp = make_pipe();
			if (!pipe_temp)
				return (NULL);
			cmd_temp->next = pipe_temp;
			pipe_temp->prev = cmd_temp;
		}
		i++;
	}
	return (list);
}

t_cmd	*get_parsed_list(char *line)
{
	char	**cmdlines;

	if (!line)
		return (NULL);
	cmdlines = sep_cmdline(line, '|');
	if (!cmdlines)
		return (NULL);
	return (make_list(cmdlines));
}
