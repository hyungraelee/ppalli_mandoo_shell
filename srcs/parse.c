#include "minishell.h"

t_cmd	*make_cmd(char *cmdline)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = make_tokenlist(cmdline);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*make_list(char **cmdlines)
{
	t_cmd	*list;
	t_cmd	*temp;
	int		i;

	i = 0;
	list = NULL;
	while (cmdlines[i])
	{
		temp = make_cmd(cmdlines[i]);
		if (!temp)
			return (NULL);
		if (list == NULL)
			list = temp;
		else
		{
			list->next = temp;
			temp->prev = list;
			list = list->next;
		}
		i++;
	}
	while (list->prev)
		list = list->prev;
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
