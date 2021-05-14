#include "minishell.h"

static int	dir_home_default(char *path, char *arg, char ***envp)
{
	char	*env_value;

	env_value = find_env_value("HOME", *envp);
	if (!env_value)
	{
		if (!arg)
			return (ft_print_err("cd", "HOME not set", NULL, 1));
	}
	else
		ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
	return (1);
}

static int	dir_oldpwd(char *path, char ***envp)
{
	char	*env_value;

	env_value = find_env_value("OLDPWD", *envp);
	if (!env_value)
		return (ft_print_err("cd", "OLDPWD not set", NULL, 1));
	else
	{
		ft_putstr_fd(env_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_strlcpy(path, env_value, ft_strlen(env_value) + 1);
	}
	return (1);
}

int			handle_special_arg(char *path, char *arg, char ***envp)
{
	if (!arg || !ft_strcmp("~", arg) || !ft_strcmp("~/", arg))
	{
		if (!dir_home_default(path, arg, envp))
			return (0);
	}
	else if (!ft_strcmp("-", arg))
	{
		if (!dir_oldpwd(path, envp))
			return (0);
	}
	return (1);
}

void		dir_start_at_home(char *path, char *arg, char ***envp)
{
	int		i;
	int		j;
	char	*env_value;

	i = -1;
	j = 1;
	env_value = find_env_value("HOME", *envp);
	while (env_value[++i])
		path[i] = env_value[i];
	while (arg[j])
		path[i++] = arg[j++];
}
