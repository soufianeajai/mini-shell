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
# include <fcntl.h>

void	exec_cmd(t_tree_node *tree, t_env **env);
void	exec_redir(t_tree_node *tree, t_env **env);
int		execute_simple_cmd(t_env **env, t_cmd_node *cmd);
int		execute_redir(t_env **env, t_redir_node *cmd);

void	execute(t_tree_node *tree, t_env **env);
int		execute_tree(t_tree_node *tree, t_env **env);

int		util_redir(t_redir_node *cmd, t_redir_type type, int fd_in, int fd_out);
int		ft_error(char *cmd, char *error);
void	sig_quit();
void	check_exit_code(int status);

#endif
