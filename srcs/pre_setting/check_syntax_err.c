#include "minishell.h"

static int	handle_last_open(char sflag, int rd)
{
	if ((sflag & REDIRECT) && rd == 1)
		return (ft_print_synerr('<', rd));
	else if (sflag & REDIRECT)
		return (ft_print_synerr('>', rd));
	else if (sflag & PIPE)
		return (ft_print_synerr('|', 0));
	else if (sflag & S_QUOTE)
		return (ft_print_synerr('\'', 0));
	else if (sflag & D_QUOTE)
		return (ft_print_synerr('\"', 0));
	else
		return (0);
}

static void	check_normal_letter(int *i, char *sflag)
{
	if (*sflag & REDIRECT)
		*sflag = (*sflag ^ REDIRECT) | POSSIBLE;
	else if (*sflag & PIPE)
	{
		*sflag ^= PIPE;
		*sflag |= CMD + POSSIBLE;
	}
	else if (!(*sflag & REDIRECT) && !(*sflag & PIPE))
		*sflag |= CMD;
	(*i)++;
}

static void	quote_flag_onoff(char *input_string, int *i, char *sflag)
{
	if (*input_string == '\'')
	{
		if (*sflag & S_QUOTE)						// if s_quote on
			*sflag ^= S_QUOTE;						// s_quote off
		else if (!(*sflag & D_QUOTE))				// if d_quote off
			*sflag |= S_QUOTE;						// s_quote on
		(*i)++;
	}												// if d_quote on -> Do not on s_quote
	else if (*input_string == '\"')
	{
		if (*sflag & D_QUOTE)						// if d_quote on
		{
			if (*(input_string - 1) != '\\')
				*sflag ^= D_QUOTE;					// d_quote off
		}
		else if (!(*sflag & S_QUOTE))				// if s_quote off
			*sflag |= D_QUOTE;						// d_quote on
		(*i)++;
	}
}

int			check_syntax_err(char *input_string)
{
	char	sflag;
	int		i;
	int		rd;

	sflag = 0;
	i = 0;
	while (input_string[i])
	{
		if (ft_strchr(IFS, input_string[i]))
			i++;
		else if (input_string[i] == '\'' || input_string[i] == '\"')
			quote_flag_onoff(&(input_string[i]), &i, &sflag);
		else if (ft_strchr("><|;", input_string[i]) && !(sflag & S_QUOTE) && !(sflag & D_QUOTE))
		{
			if (!handle_special_letter(&(input_string[i]), &i, &sflag, &rd))
				return (0);
		}
		else
			check_normal_letter(&i, &sflag);
	}
	if ((sflag & REDIRECT) || (sflag & PIPE) || (sflag & S_QUOTE) || (sflag & D_QUOTE))		// if redirect or pipe on at the end (echo 123 > )
		return (handle_last_open(sflag, rd));
	return (1);
}
