/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_smp_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:29:20 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:29:22 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	run_cmd(t_env **env, char *path_cmd, t_cmd_node *cmd)
{
	char	**arr;
	int		exit_code;

	arr = lst_to_arr(*env);
	if (execve(path_cmd, cmd->arguments, arr) == -1)
	{
		exit_code = check_path(path_cmd, cmd->executable, 1);
		free(path_cmd);
		return (exit_code);
	}
	return (0);
}

int	handle_null_path(t_env **env, t_cmd_node *cmd)
{
	char	*new_path;
	char	*path_;

	path_ = ft_getenv(*env, "PATH");
	new_path = ft_strjoin(getcwd(NULL, 0), "/", 1);
	new_path = ft_strjoin(new_path, cmd->executable, 1);
	if (check_path(new_path, cmd->executable, 0))
		return (check_path(new_path, cmd->executable, 1));
	if (!path_ && execve(new_path, cmd->arguments, NULL) != -1)
		return (0);
	else
		return (ft_error(cmd->executable, "command not found"));
	free(new_path);
}
