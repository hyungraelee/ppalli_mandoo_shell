#include "minishell.h"

static char	**init_envp(char **env)
{
	int		i;
	int		j;
	char	**envp;

	i = -1;
	while (env[++i])
		;
	envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
	{
		envp[i] = (char *)ft_calloc(PATH_MAX + 1, sizeof(char));
		j = -1;
		while (env[i][++j])
			envp[i][j] = env[i][j];
		envp[i][j] = 0;
	}
	envp[i] = NULL;
	return (envp);
}

static void	init_termios(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag &= ~ECHO;		// 입력시 터미널에 보이지 않도록
	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	init_termcap(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putstr_fd("minishell: Specify a terminal \
type with `setenv TERM <yourtype>'.", STDERR_FILENO);
		exit(1);
	}
	success = tgetent(NULL, "xterm");
	if (success < 0)
	{
		ft_putstr_fd("minishell: Could not access the \
termcap data base.", STDERR_FILENO);
		exit(1);
	}
	if (success == 0)
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: \
Terminal type `", termtype, 2), "\' is not defined.", 1), STDERR_FILENO);
		exit(1);
	}
}

char		**init(char **env)
{
	char	**envp;

	init_termios();
	init_termcap();
	envp = init_envp(env);
	return (envp);
}
