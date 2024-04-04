/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:18:35 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/02 03:18:39 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../environnement/env.h"
# include "../parsing/parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	exec_cmd(t_tree_node *tree, t_env **env);
void	exec_redir(t_tree_node *tree, t_env **env);
int		execute_simple_cmd(t_env **env, t_cmd_node *cmd);
int		execute_redir(t_env **env, t_redir_node *cmd);
int		ft_error(char *cmd, char *error);
int		check_type(int flag, char *path, struct stat path_stat, char *cmd);
int		check_path(char *path, char *cmd, int flag);
char	**lst_to_arr(t_env *env);
void	execute(t_tree_node *tree, t_env **env);
int		execute_tree(t_tree_node *tree, t_env **env);
int		handle_null_path(t_env **env, t_cmd_node *cmd);
int		run_cmd(t_env **env, char *path_cmd, t_cmd_node *cmd);
int		util_redir(t_redir_node *cmd, t_redir_type type, int fd_in, int fd_out);
int		ft_error(char *cmd, char *error);
void	sig_quit(void);
void	check_exit_code(int status);
void	execute_child(int *fd, int flag, t_pipe_node *pipe_node, t_env **env);
void	error_pipe(int *fd);
int		exit_pipe(int last_pid);
#endif
