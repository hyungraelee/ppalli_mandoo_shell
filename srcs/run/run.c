#include "minishell.h"

int run(t_cmd *cmd_list, char ***envp)
{
	int i;
	struct stat buf;

	while (cmd_list)
	{
		cmd_list->cmd_name = get_env_value(cmd_list->cmd_name, *envp);
		if (!cmd_list->cmd_name)
			handle_no_cmd(cmd_list, envp);
		else
		{
			i = -1;
			while (++i < BLTIN_NUM)
			{
				if (!ft_strcmp(cmd_list->cmd_name, builtin_str(i)))
				{
					blt_run(i, cmd_list, envp);
					break;
				}
			}
			if (i >= BLTIN_NUM)
			{
				if (!stat(cmd_list->cmd_name, &buf) && S_ISDIR(buf.st_mode))
					ft_print_err(cmd_list->cmd_name, "is a directory", NULL, 126);
				else if (!stat(cmd_list->cmd_name, &buf) && !(buf.st_mode & S_IXUSR))
					ft_print_err(cmd_list->cmd_name, "Permission denied", NULL, 126);
				else if (!stat(cmd_list->cmd_name, &buf))
					run_process(cmd_list, envp);
				else
					find_cmd_path(cmd_list, *envp);
			}
		}
		if (cmd_list->next)
			cmd_list = cmd_list->next;
		else
			break;
	}
	return (1);
}
