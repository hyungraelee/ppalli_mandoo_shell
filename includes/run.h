/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkeum <jkeum@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:59:02 by jkeum             #+#    #+#             */
/*   Updated: 2021/05/16 17:59:03 by jkeum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minishell.h"

# define BLTIN_NUM 7

int		run(t_cmd *cmd_list, char ***envp);

int		handle_no_cmd(t_cmd *cmd_list, char ***envp);

char	*builtin_str(int i);
void	blt_run(int i, t_cmd *cmd_list, char ***envp);

int		run_process(t_cmd *cmd_list, char ***envp);

char	*get_env_value(char *arg, char **envp);
int		find_cmd_path(t_cmd *cmd_list, char **envp);
char	*find_env_value(char *env_name, char **envp);
int		find_env_name(char *env_name, char **envp);

void	pipe_process(t_cmd *cmd_list);
void	pipe_close(t_cmd *cmd_list);
void	pipe_restore(t_cmd *cmd_list, int *old_fds);
int		redirect_process(t_token *token, int *rd_fds);
void	redirect_close(int *rd_fds);
void	redirect_restore(int *rd_fds, int *old_fds);

int		blt_echo(t_token *token, char ***envp);
int		blt_env(t_token *token, char ***envp);
int		set_env_name(char **export_name, char **envp);
char	*set_env_value(char *arg, int idx);
char	*set_export_value(char *arg, int idx, char **envp);
int		blt_exit(t_token *token, char ***envp);
int		blt_cd(t_token *token, char ***envp);
int		handle_special_arg(char *path, char *arg, char ***envp);
void	dir_start_at_home(char *path, char *arg, char ***envp);
int		blt_pwd(t_token *token, char ***envp);
int		blt_export(t_token *token, char ***envp);
char	*set_export_value(char *arg, int idx, char **envp);
void	print_export(char **envp);
void	print_export_value(char *envp, int idx, int fd);
void	sort_export(char ***export, int i);
int		blt_unset(t_token *token, char ***envp);
int		turn_on_flag(int *flag, int quote, int idx);
void	sig_handler(int signo);

char	**add_env(char **envp, char *str);
char	**delete_env(char **envp, char *str, int idx);

int		is_pipe_exist(t_cmd *cmd_list);

void	replace_env_in_arg(t_cmd *cmd_list, char ***envp);

void	save_old_fds(int *old_fds);

void	free_minishell(t_minishell *shell);
void	free_token(t_token *token);
void	free_cmdlist(t_cmd *cmd_list);
void	free_str(char *str);
void	free_double_arr(char **arr);

#endif
