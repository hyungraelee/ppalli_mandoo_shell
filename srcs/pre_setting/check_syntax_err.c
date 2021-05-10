#include "minishell.h"

int		redirect_flag_onoff(char *input_string, int *i, char *sflag, int *rd)
{
	if (*sflag & REDIRECT)	// if redirect already on (echo 123 > > file)
	{
		if (*input_string == '>' && *(input_string + 1) == '>')
			return (ft_print_synerr(*input_string, 3));
		else 								// syntax err
			return (ft_print_synerr(*input_string, 0));
	}
	*sflag |= REDIRECT;							// redirect on
	if (*input_string == '>' && *(input_string + 1) == '>')	// if append case
	{
		(*i) += 2;
		*rd = 3;
	}
	else if (*input_string == '>' && *(input_string + 1) != '>')		// if not append case
	{
		(*i)++;
		*rd = 2;
	}
	else
	{
		(*i)++;
		*rd = 1;
	}
	return (1);
}

void	quote_flag_onoff(char *input_string, int *i, char *sflag)
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

int		check_syntax_err(char *input_string)
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
		else if ((input_string[i] == '>' || input_string[i] == '<') && !(sflag & S_QUOTE) && !(sflag & D_QUOTE))
		{	// when outside quote
			if (!redirect_flag_onoff(&(input_string[i]), &i, &sflag, &rd))
			// if (rd == 0)
				return (0);
		}
		else if (input_string[i] == '|' && !(sflag & S_QUOTE) && !(sflag & D_QUOTE))
		{	// when outside quote
			if (sflag & REDIRECT)						// if redirect on	(>  | )
				return (ft_print_synerr(input_string[i], 0));								// syntax err
			if (!(sflag & POSSIBLE) && !(sflag & CMD))	// if impossible and cmd off (    | | )
				return (ft_print_synerr(input_string[i], 0));								// syntax err
			sflag |= PIPE;								// pipe on
			sflag ^= CMD + POSSIBLE;					// cmd and possible off
			i++;
		}
		else if (input_string[i] == ';' && !(sflag & S_QUOTE) && !(sflag & D_QUOTE))
		{	// when outside quote
			if ((sflag & REDIRECT) || (sflag & PIPE))	// if redirect or pipe on (echo 123 > ;)
				return (ft_print_synerr(input_string[i], 0));								// syntax err
			if (!(sflag & CMD) && !(sflag & POSSIBLE))	// if cmd and possible off (  ;) (echo 123;;)
				return (ft_print_synerr(input_string[i], 0));								// syntax err
			sflag = 0;									// flag zero set
			i++;
		}
		else
		{
			if (sflag & REDIRECT)
				sflag = (sflag ^ REDIRECT) | POSSIBLE;
			else if (sflag & PIPE)
			{
				sflag ^= PIPE;
				sflag |= CMD + POSSIBLE;
			}
			else if (!(sflag & REDIRECT) && !(sflag & PIPE))
				sflag |= CMD;
			i++;
		}
	}
	if ((sflag & REDIRECT) || (sflag & PIPE) || (sflag & S_QUOTE) || (sflag & D_QUOTE))		// if redirect or pipe on at the end (echo 123 > )
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
	}
	return (1);
}

// int main()
// {
// 	// char a = 1;
// 	// printf("%d\n", a & 1);
// 	if(!check_syntax_err("echo > ; fed < ede >> edsd"))
// 		printf("\nsyntax error\n\n");
// 	return (0);
// }
