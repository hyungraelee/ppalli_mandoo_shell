#include "minishell.h"

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	delete_letter(void)
{
	tputs(tgetstr("le", NULL), 1, putchar_tc);
	tputs(tgetstr("dc", NULL), 1, putchar_tc);
}

void	delete_current_line(void)
{
	tputs(tgetstr("dl", NULL), 1, putchar_tc);
}
