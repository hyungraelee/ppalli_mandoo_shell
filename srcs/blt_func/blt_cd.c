#include "minishell.h"

void	change_dir(char *dest, char ***envp)
{

}

int		exec_cd(t_token *tok, char ***envp)
{
	char	dest[PATH_MAX + 1];
	int		i;
	int		j;
	// t_token	*path;
	char	*env_value;

	// if (ft_strlen(cmd_list->token->next->arg) > 255)
		// error
	i = 0;
	while (i < PATH_MAX + 1)
		dest[i++] = 0;
	while (path->type)
	path = cmd_list->token->next;
	i = -1;
	if (!path || !ft_strcmp("~", path->arg) || !ft_strcmp("~/", path->arg))
	{
		// i = 0;
		env_value = find_env_value("HOME", *envp);
		while (*env_value)
			dest[++i] = (*env_value)++;
	}
	else if (path->arg[0] == '~' && path->arg[1] == '/' && ft_strlen(path->arg) > 2)
	{
		// i = 0;
		env_value = find_env_value("HOME", *envp);
		while (*env_value)
			dest[++i] = (*env_value)++;
		j = 2;
		while (path->arg[j])
			dest[i++] = path->arg[j++];
	}
	else if (!ft_strcmp("-", path->arg))
	{
		// print OLDPWD
		// i = 0;
		env_value = find_env_value("OLDPWD", *envp);
		while (*env_value)
			dest[++i] = (*env_value)++;
	}
	else
	{
		// i = 0;
		while (path->arg[++i])
			dest[i] = path->arg[i];
	}
	change_dir(dest, envp);
}

int		blt_cd(t_cmd *cmd_list, char **envp)
{
	pid_t	pid;
	int		rd_fds[2];
	int		status;

	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list, rd_fds);
			exec_cd(cmd_list->token, &envp);
			exit(0);
		}
		else if (pid == -1)
			; // error
		else
		{
			wait(&status);
			redirect_close(cmd_list, rd_fds);
			pipe_close(cmd_list);
		}
		return (1);
	}
	else
		exec_cd(cmd_list->token, &envp);
	return (1);
}
