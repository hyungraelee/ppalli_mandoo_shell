#include "minishell.h"

char	*builtin_str(int i)
{
	char	*blt_str[BLTIN_NUM + 1];

	blt_str[0] = "echo";
	blt_str[1] = "cd";
	blt_str[2] = "pwd";
	blt_str[3] = "export";
	blt_str[4] = "unset";
	blt_str[5] = "env";
	blt_str[6] = "exit";
	blt_str[7] = NULL;
	return (blt_str[i]);
}

int		(*builtin_func(int i))(t_token *token, char ***envp)
{
	int		(*blt_func[BLTIN_NUM])(t_token *token, char ***envp);

	blt_func[0] = &blt_echo;
	blt_func[1] = &blt_cd;
	blt_func[2] = &blt_pwd;
	blt_func[3] = &blt_export;
	blt_func[4] = &blt_unset;
	blt_func[5] = &blt_env;
	blt_func[6] = &blt_exit;
	return (blt_func[i]);
}

void blt_run(int i, t_cmd *cmd_list, char ***envp)
{
	int status;
	int rd_fds[2];
	int old_fds[2];

	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
	if (ft_strcmp(cmd_list->cmd_name, "export") && ft_strcmp(cmd_list->cmd_name, "env"))
	{
		while (cmd_list->token)
		{
			cmd_list->token->arg = get_env_value(cmd_list->token->arg, *envp);
			if (cmd_list->token->next)
				cmd_list->token = cmd_list->token->next;
			else
				break;
		}
		while (cmd_list->token->prev)
			cmd_list->token = cmd_list->token->prev;
	}
	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		g_global.pid = fork();
		if (g_global.pid == 0)
		{
			pipe_process(cmd_list);
			if (!redirect_process(cmd_list->token, rd_fds))
				exit(1);
			(*builtin_func(i))(cmd_list->token, envp);
			exit(0);
		}
		else if (g_global.pid == -1)
			ft_print_err("fork", strerror(errno), NULL, 1);
		else
		{
			wait(&status);
			if (status >> 8 != 0)
				g_global.exit = status >> 8;
			redirect_close(rd_fds);
			pipe_restore(cmd_list, old_fds);
		}
	}
	else
	{
		if (!redirect_process(cmd_list->token, rd_fds))
		{
			redirect_restore(rd_fds, old_fds);
			return;
		}
		(*builtin_func(i))(cmd_list->token, envp);
		redirect_restore(rd_fds, old_fds);
	}
}
