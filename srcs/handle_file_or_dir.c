#include "minishell.h"

int	handle_file_or_dir(char	*cmd_name, char ***envp)
{
	struct stat	buf;

	cmd_name = get_env_value(cmd_name, *envp);
	if (stat(cmd_name, &buf) == -1)
	{
		printf("minishell: %s: %s\n", cmd_name, strerror(errno));
		g_exit = 127;
	}
	if (S_ISDIR(buf.st_mode))
	{
		printf("minishell: %s: %s\n", cmd_name, "is a directory");
		g_exit = 126;
	}
	else if (S_ISREG(buf.st_mode))
	{
		if (buf.st_mode & S_IXUSR)
			g_exit = 0;
		else
		{
			printf("minishell: %s: %s\n", cmd_name, "Permission denied");
			g_exit = 126;
		}
	}
	return (1);
}
