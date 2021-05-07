#include "minishell.h"

int		nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_current_cursor(int *row, int *col)
{
	char	buf[255];
	int		ret;
	int		i;
	int		check_row;
	int		num_len;

	write(1, QUERY_CURSOR_POSITION, 4);
	ret = read(0, buf, 254);			// 왜 254만큼 읽는지, 무슨일 발생하는지 확인.
	buf[ret] = '\0';
	i = 0;
	check_row = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			if (!check_row)
			{
				*row = ft_atoi(&buf[i]) - 1;
				num_len = nbr_length(*row + 1);
			}
			else
			{
				*col = ft_atoi(&buf[i]) - 1;
				break ;
			}
			check_row++;
			i += num_len;
		}
		i++;
	}
	// printf("%d %d", *row, *col);
}

int	read_cmd(char **input_string)
{
	int	c;
	int	col;

	*input_string = NULL;
	col = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		// get_current_cursor(&row, &col);
		if (c == BACKSPACE)
		{
			if (col-- > 0)
				delete_letter();
			if (col < 0)
				col = 0;
		}
		// else if (c == LEFT_ARROW)
		// else if (c == RIGHT_ARROW)
		// else if (c == UP_ARROW)
		// else if (c == DOWN_ARROW)
		else if (c == ENTER)
		{
			write(1, &c, 1);
			break;
		}
		else
		{
			write(1, &c, 1);
			col++;
			*input_string = ft_str_char_join(*input_string, c);
		}
		c = 0;
	}
	return (1);
}
