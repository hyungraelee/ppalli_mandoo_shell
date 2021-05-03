#include "minishell.h"

char	**add_env(char **envp, char *str)
{
	char	**result;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return (NULL);
	i = -1;
	while (envp[++i])
		result[i] = envp[i];
	result[i] = (char *)ft_calloc((PATH_MAX + 1), sizeof(char));
	ft_strlcpy(result[i], str, ft_strlen(str) + 1);
	result[++i] = NULL;
	free(envp);
	return (result);
}

void	change_dir(char *dest, char ***envp)
{
	int		rt;
	char	*sys_env;
	char	*inner_env;
	char	*temp;
	char	buf[1024];
	char	*pwd;

	rt = chdir(dest);
	char	cwd[1024];
	printf("%s\n", getcwd(cwd, 100));
	sys_env = NULL;
	inner_env = NULL;
	// if (rt == -1)
		// strerror error & exit
	// else
	temp = find_env_value("PWD", *envp);
	pwd = getcwd(buf, 1024);

	inner_env = find_env_value("OLDPWD", *envp);
	if (!inner_env)
		*envp = add_env(*envp, ft_strjoin("OLDPWD=", temp, 0));
	else
		ft_strlcpy(find_env_value("OLDPWD", *envp), temp, ft_strlen(temp) + 1);
	temp = find_env_value("PWD", *envp);
	ft_strlcpy(find_env_value("PWD", *envp), pwd, ft_strlen(pwd) + 1);
}

int		exec_cd(t_token *token, char ***envp)
{
	char	path[PATH_MAX + 1];
	int		i;
	int		j;
	char	*arg;
	char	*env_value;

	i = -1;
	while (++i < PATH_MAX + 1)
		path[i] = 0;
	while (token->type != ARGUMENT)
	{
		if (token->next)
			token = token->next;
		else
			break ;
	}
	if (token->type == ARGUMENT)
		arg = get_env_value(token->arg, *envp);
	else
		arg = NULL;
	i = -1;
	if (!arg || !ft_strcmp("~", arg) || !ft_strcmp("~/", arg))
	{
		env_value = find_env_value("HOME", *envp);
		if (!env_value)
		{
			;
			// if (!arg)
				// error : "HOME not set" -> $? = 1
			// else if (!ft_strcmp("~", arg) || !ft_strcmp("~/", arg))
				// change dir to home
		}
		else
		{
			ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
		}
	}
	else if (arg[0] == '~' && arg[1] == '/' && ft_strlen(arg) > 2)
	{
		env_value = find_env_value("HOME", *envp);
		while (env_value[++i])
			path[i] = env_value[i];
		j = 2;
		while (arg[j])
			path[i++] = arg[j++];
	}
	else if (!ft_strcmp("-", arg))
	{
		env_value = find_env_value("OLDPWD", *envp);
		if (!env_value)
		{
			;
			// error : "OLDPWD not set" -> $? = 1
		}
		else
		{
			ft_putstr_fd(env_value, STDOUT_FILENO);
			ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
		}
	}
	else
	{
		while (arg[++i])
			path[i] = arg[i];
	}
	change_dir(path, envp);
	return (1);
}

int		blt_cd(t_cmd *cmd_list, char **envp)
{
	pid_t	pid;
	int		rd_fds[2];
	int		status;
	int		old_fds[2];

	if (cmd_list->prev || cmd_list->next)
	{
		pipe(cmd_list->fds);
		pid = fork();
		if (pid == 0)
		{
			pipe_process(cmd_list);
			redirect_process(cmd_list->token, rd_fds);
			exec_cd(cmd_list->token, &envp);
			exit(0);
		}
		else if (pid == -1)
			; // error
		else
		{
			wait(&status);
			redirect_close(rd_fds);
			pipe_close(cmd_list);
		}
		return (1);
	}
	else
	{
		old_fds[0] = dup(STDIN_FILENO);
		old_fds[1] = dup(STDOUT_FILENO);
		redirect_process(cmd_list->token, rd_fds);
		exec_cd(cmd_list->token, &envp);
		redirect_restore(rd_fds, old_fds);
	}
	return (1);
}
