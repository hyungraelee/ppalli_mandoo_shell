#ifndef RUN_H
# define RUN_H

# include "minishell.h"

# define BLTIN_NUM 7

char	*builtin_str(int i);
int		(*builtin_func(int i))(t_cmd *cmd_list);
int		run(t_cmd *cmd_list, char **envp);
int		run_process(t_cmd *cmd_list, char **envp);
int		find_cmd_path(t_cmd *cmd_list, char **envp);
char	*find_env_value(char *env_name, char **envp);
void	pipe_process(t_cmd *cmd_list);
void	pipe_close(t_cmd *cmd_list);
void	redirect_process(t_token *token, int *rd_fds);
void	redirect_close(int *rd_fds);
void	redirect_restore(int *rd_fds, int *old_fds);
int		blt_echo(t_cmd *cmd_list, char **envp);

#endif
