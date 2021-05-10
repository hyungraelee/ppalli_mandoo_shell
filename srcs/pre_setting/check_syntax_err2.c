#include "minishell.h"


static int		semicolon_flag_onoff(char input_string, int *i, char *sflag)
{
	if ((*sflag & REDIRECT) || (*sflag & PIPE))	// if redirect or pipe on (echo 123 > ;)
		return (ft_print_synerr(input_string, 0));								// syntax err
	if (!(*sflag & CMD) && !(*sflag & POSSIBLE))	// if cmd and possible off (  ;) (echo 123;;)
		return (ft_print_synerr(input_string, 0));								// syntax err
	*sflag = 0;									// flag zero set
	(*i)++;
	return (1);
}

static int		pipe_flag_onoff(char input_string, int *i, char *sflag)
{
	if (*sflag & REDIRECT)						// if redirect on	(>  | )
		return (ft_print_synerr(input_string, 0));								// syntax err
	if (!(*sflag & POSSIBLE) && !(*sflag & CMD))	// if impossible and cmd off (    | | )
		return (ft_print_synerr(input_string, 0));								// syntax err
	*sflag |= PIPE;								// pipe on
	*sflag ^= CMD + POSSIBLE;					// cmd and possible off
	(*i)++;
	return (1);
}

static int		redirect_flag_onoff(char *input_string, int *i, char *sflag, int *rd)
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

int		handle_special_letter(char *input_string, int *i, char *sflag, int *rd)
{
	if (*input_string == '>' || *input_string == '<')
	{
		if (!redirect_flag_onoff(input_string, i, sflag, rd))
			return (0);
	}
	else if (*input_string == '|')
	{
		if (!pipe_flag_onoff(*input_string, i, sflag))
			return (0);
	}
	else if (*input_string == ';')
	{
		if (!semicolon_flag_onoff(*input_string, i, sflag))
			return (0);
	}
	return (1);
}
