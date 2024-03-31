/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:24:17 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/30 23:24:20 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_builtin(t_cmd_node *cmd)
{
	if (!cmd || !cmd->executable)
		return (0);
	if (ft_strncmp(cmd->executable, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->executable, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_env **env, t_cmd_node *cmd)
{
	if (ft_strncmp(cmd->executable, "echo", 5) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->executable, "cd", 3) == 0)
		return (ft_cd(env, cmd));
	if (ft_strncmp(cmd->executable, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd->executable, "export", 7) == 0)
		return (ft_export(env, cmd));
	if (ft_strncmp(cmd->executable, "unset", 6) == 0)
		return (ft_unset(env, cmd));
	if (ft_strncmp(cmd->executable, "env", 4) == 0)
		return (ft_env(*env));
	if (ft_strncmp(cmd->executable, "exit", 5) == 0)
		return (ft_exit(cmd, env));
	return (0);
}
