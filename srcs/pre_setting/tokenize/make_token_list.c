#include "minishell.h"

static t_token	*token_init(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->arg = NULL;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

static void		rd_token(t_token **result, char *args)
{
	if (args[0] == '<')
	{
		(*result)->type = RD_IN;
		(*result)->arg = ft_strtrim(args, "<");
	}
	else if (args[0] == '>' && args[1] != '>')
	{
		(*result)->type = RD_OUT;
		(*result)->arg = ft_strtrim(args, ">");
	}
	else if (args[0] == '>' && args[1] == '>')
	{
		(*result)->type = RD_APPEND;
		(*result)->arg = ft_strtrim(args, ">>");
	}
}

static t_token	*make_token(char *args, int command)
{
	t_token	*result;

	result = token_init();
	if (!result)
		return (0);
	if (args[0] == '<' || args[0] == '>')
		rd_token(&result, args);
	else
	{
		if (command == 0)
			result->type = COMMAND;
		else
			result->type = ARGUMENT;
		result->arg = ft_strdup(args);
	}
	return (result);
}

static void		connect_list(t_token **token, t_token **temp)
{
	if (!(*token))
		(*token) = (*temp);
	else
	{
		(*token)->next = *temp;
		(*temp)->prev = *token;
		*token = (*token)->next;
	}
}

t_token			*make_token_list(char **args, char **cmd_name)
{
	t_token	*token;
	t_token	*temp;
	int		i;
	int		command;

	i = 0;
	command = 0;
	token = NULL;
	while (args[i])
	{
		temp = make_token(args[i], command);
		if (temp->type == COMMAND)
		{
			*cmd_name = ft_strjoin(*cmd_name, temp->arg, 1);
			command = 1;
		}
		connect_list(&token, &temp);
		free(args[i]);
		i++;
	}
	free(args);
	while (token->prev)
		token = token->prev;
	return (token);
}
