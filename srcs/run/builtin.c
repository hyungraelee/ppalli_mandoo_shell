/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:00:10 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 18:12:17 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*builtin_str(int i)
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

static int	(*builtin_func(int i))(t_token *token, char ***envp)
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

static void	pipe_blt_run(int i, t_cmd *cmd_list, char ***envp)
{
	int	rd_fds[2];
	int	old_fds[2];
	int	status;

	save_old_fds(old_fds);
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

void		blt_run(int i, t_cmd *cmd_list, char ***envp)
{
	int rd_fds[2];
	int old_fds[2];

	save_old_fds(old_fds);
	if (ft_strcmp(cmd_list->cmd_name, "export") && \
	ft_strcmp(cmd_list->cmd_name, "env"))
		replace_env_in_arg(cmd_list, envp);
	if (is_pipe_exist(cmd_list))
		pipe_blt_run(i, cmd_list, envp);
	else
	{
		if (!redirect_process(cmd_list->token, rd_fds))
		{
			redirect_restore(rd_fds, old_fds);
			return ;
		}
		(*builtin_func(i))(cmd_list->token, envp);
		redirect_restore(rd_fds, old_fds);
	}
}
