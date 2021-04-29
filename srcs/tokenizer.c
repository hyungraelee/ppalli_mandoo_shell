#include "minishell.h"

t_token	*token_init(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->arg = NULL;
	token->blank = 0;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_token	*token_squote_str(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = STR;
	while (cmdline[++(*i)] != '\'')
	{
		token->arg = ft_str_char_join(token->arg, cmdline[*i]);
		if (!token->arg)
			return (0);
	}
	++(*i);
	return (token);
}

t_token	*token_escape(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = STR;
	++(*i);
	token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*token_unescape(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = STR;
	token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*token_env(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = ENV;
	while (!ft_strchr(IFS, cmdline[++(*i)]))
		token->arg = ft_str_char_join(token->arg, cmdline[*i]);
	return (token);
}

t_token	*token_redirection(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	if (cmdline[*i] == '>')
	{
		if (cmdline[*i + 1] == '>')
		{
			(*i)++;
			token->type = RD_APPEND;
		}
		else
			token->type = RD_OUT;
	}
	else
		token->type = RD_IN;
	(*i)++;
	while (ft_strchr(IFS, cmdline[*i]))
		(*i)++;
	while (!ft_strchr(IFS, cmdline[*i]))
		token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*token_option(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = OPTION;
	while (!ft_strchr(IFS, cmdline[(*i)]))
		token->arg = ft_str_char_join(token->arg,cmdline[(*i)++]);
	return (token);
}

t_token	*token_normal_str(char *cmdline, int *i, int type)
{
	t_token	*token;

	token = token_init();
	token->type = STR;
	if (type != COMMAND && type != OPTION && ft_strchr(IFS, cmdline[*i - 1]))
		token->blank = 1;
	while (!ft_strchr(" \t\n\\`\"$><\'", cmdline[*i]))
		token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*token_dquote_str(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = STR;
	while (!ft_strchr("\\`\"$><\'", cmdline[*i]))
		token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*token_command(char *cmdline, int *i)
{
	t_token	*token;

	token = token_init();
	token->type = COMMAND;
	while (!ft_strchr(IFS, cmdline[*i]))
		token->arg = ft_str_char_join(token->arg, cmdline[(*i)++]);
	return (token);
}

t_token	*make_tokenlist(char *cmdline, char **cmd_name)
{
	t_token	*token;
	t_token	*tmp;
	int		i;
	int		flag;

	token = NULL;
	i = 0;
	flag = 0;
	while (cmdline[i])
	{
		if (ft_strchr(IFS, cmdline[i]) && !(flag & S_QUOTE) && !(flag & D_QUOTE))
			i++;
		else
		{
			if (cmdline[i] == '\'' && !(flag & D_QUOTE))
				tmp = token_squote_str(cmdline, &i);
			else if (cmdline[i] == '\"' && !(flag & S_QUOTE))
			{
				if (!(flag & D_QUOTE))
					flag |= D_QUOTE;
				else
					flag ^= D_QUOTE;
				i++;
				continue ;
			}
			else if (cmdline[i] == '\\' && (flag & D_QUOTE))
			{	// ex) echo "hello \" world"
				if (ft_strchr("`\\\"$", cmdline[i + 1]))
					tmp = token_escape(cmdline, &i);
				else
					tmp = token_unescape(cmdline, &i);
			}
			else if (cmdline[i] == '$')		//always env
				tmp = token_env(cmdline, &i);
			else if ((cmdline[i] == '>' || cmdline[i] == '<') && !(flag & D_QUOTE))
				tmp = token_redirection(cmdline, &i);
			else if (cmdline[i] == '-' && !(flag & D_QUOTE) &&
			(token->type == COMMAND || token->type == OPTION))
				tmp = token_option(cmdline, &i);
			else
			{
				if (!(flag & CMD))	// when cmd flag off
				{
					tmp = token_command(cmdline, &i);
					*cmd_name = ft_strdup(tmp->arg);
					flag |= CMD;
				}
				else if (!(flag & D_QUOTE))
					tmp = token_normal_str(cmdline, &i, token->type);
				else if (flag & D_QUOTE)
					tmp = token_dquote_str(cmdline, &i);
			}
			if (!token)
				token = tmp;
			else
			{
				tmp->prev = token;
				token->next = tmp;
				token = token->next;
			}
		}
	}
	while (token->prev)
		token = token->prev;
	return (token);
}

// int		main(void)
// {
// 	t_token	*token;

// 	token = make_tokenlist("> file echo -n \"hello while      a\\\" \\$HOME \"hihi < file1 >>file2   $PWD    gogijoa\'joa\\\'  < file3");
// 	while (token->next)
// 	{
// 		printf("type = %d arg = %s\n", token->type, token->arg);
// 		token = token->next;
// 	}
// 	printf("type = %d arg = %s\n", token->type, token->arg);
// 	return (0);
// }

// \"hello while\\\" $HOME \"hihi < file1 >>file2       gogijoa\'joa\\\'  < file3
