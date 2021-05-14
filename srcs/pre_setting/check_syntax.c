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
		if (*sflag & S_QUOTE)
			*sflag ^= S_QUOTE;
		else if (!(*sflag & D_QUOTE))
			*sflag |= S_QUOTE;
		(*i)++;
	}
	else if (*input_string == '\"')
	{
		if (*sflag & D_QUOTE)
			*sflag ^= D_QUOTE;
		else if (!(*sflag & S_QUOTE))
			*sflag |= D_QUOTE;
		(*i)++;
	}
}

int			check_syntax(char *s)
{
	char	f;
	int		i;
	int		rd;

	f = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr(IFS, s[i]))
			i++;
		else if (s[i] == '\'' || s[i] == '\"')
			quote_flag_onoff(&(s[i]), &i, &f);
		else if (ft_strchr("><|;", s[i]) && !(f & S_QUOTE) && !(f & D_QUOTE))
		{
			if (!handle_special_letter(&(s[i]), &i, &f, &rd))
				return (0);
		}
		else if (s[i] == '\\' && (f & D_QUOTE))
			i += 2;
		else
			check_normal_letter(&i, &f);
	}
	if ((f & REDIRECT) || (f & PIPE) || (f & S_QUOTE) || (f & D_QUOTE))
		return (handle_last_open(f, rd));
	return (1);
}
