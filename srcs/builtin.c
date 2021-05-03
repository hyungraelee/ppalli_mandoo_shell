#include "minishell.h"

char	*builtin_str(int i)
{
	char	*blt_str[BLTIN_NUM + 1];

	blt_str[0] = "echo";
	blt_str[1] = "cd";
	blt_str[2] = "pwd";
	blt_str[3] = NULL;
	// blt_str[3] = "export";
	// blt_str[4] = "unset";
	// blt_str[5] = "env";
	// blt_str[6] = "exit";
	// blt_str[7] = NULL;
	return (blt_str[i]);
}

int		(*builtin_func(int i))(t_token *token, char **envp)
{
	int		(*blt_func[BLTIN_NUM])(t_token *token, char **envp);

	blt_func[0] = &blt_echo;
	blt_func[1] = &blt_cd;
	blt_func[2] = &blt_pwd;
	// blt_func[3] = &blt_export;
	// blt_func[4] = &blt_unset;
	// blt_func[5] = &blt_env;
	// blt_func[6] = &blt_exit;
	return (blt_func[i]);
}
