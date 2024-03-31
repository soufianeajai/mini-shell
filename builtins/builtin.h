/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:35:47 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/31 00:35:48 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../environnement/env.h"
# include "../parsing/parsing.h"
# include <limits.h>

int		is_builtin(t_cmd_node *cmd);
int		execute_builtin(t_env **env, t_cmd_node *cmd);
int		ft_echo(t_cmd_node *cmd);
int		ft_pwd(void);
int		ft_cd(t_env **env, t_cmd_node *cmd);
int		ft_env(t_env *env);
int		ft_unset(t_env **env, t_cmd_node *cmd);
void	remove_env(t_env **env, char *key);
int		ft_export(t_env **env, t_cmd_node *cmd);
int		print_error_export(char *arg);
int		ft_exit(t_cmd_node *cmd, t_env **env);

#endif
