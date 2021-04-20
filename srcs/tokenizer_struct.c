#include "minishell.h"

int	info_rd(t_cmdline **cmdline, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<')
		(*cmdline)->rd_type = RD_IN;
	else if (str[i] == '>')
	{
		(*cmdline)->rd_type = RD_OUT;
		if (str[i + 1] == '>')
		{
			(*cmdline)->rd_type = RD_OUT_APPEND;
			i++;
		}
	}
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	(*cmdline)->rd = ft_substr(str, 0, i);
	return (i);
}

t_cmdline	*info_cmdline(char *str, int idx)
{
	int			i;
	int			j;
	t_cmdline	*cmdline;

	cmdline = (t_cmdline *)malloc(sizeof(t_cmdline));
	if (!cmdline)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	j = i;
	while (i < idx)
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i = info_rd(&cmdline, str);
			j = i;
		}
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			cmdline->cmd = ft_substr(str, j, i - j);
			while (str[i] == ' ')
				i++;
			if (str[i] == '-')
				cmdline->cmd = ft_strjoin_free(ft_substr(str + i, 0, 2));
			break;
		}
		i++;
	}
	cmdline->arg = ft_strjoin_free(str + i);
	if (!cmdline->cmd || !cmdline->arg)
		return (NULL);
	return (cmdline);
}

t_pipe	*init_pipe()
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->fd[0] = 0;
	pipe->fd[1] = 0;
	pipe->in = NULL;
	pipe->out = NULL;
	return (pipe);
}

t_token	*make_cmdline(char *str, int idx)
{
	t_token		*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->by_type = info_cmdline(str, idx);
	if (!node->by_type)
		return (NULL);
	node->l_child = NULL;
	node->r_child = NULL;
	return (node);
}

t_token	*make_head(char *str, int type, int idx)
{
	t_token		*head;

	head = (t_token *)malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	if (type == TYPE_PIPE)
	{
		head->by_type = init_pipe();
		head->l_child = make_cmdline(str, idx);
		head->l_child->parent = head;
	}
	else if (type == TYPE_CMD)
	{
		head->by_type = info_cmdline(str, idx);
		head->l_child = NULL;
	}
	head->parent = NULL;
	head->r_child = NULL;
	return (head);
}

t_token	*make_tree(char *line, t_token *head)
{
	t_token	*node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (!head)
				head = make_head(line, TYPE_PIPE, i - j);
			j = i;
		}
	}
}