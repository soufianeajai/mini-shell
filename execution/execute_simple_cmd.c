/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:18:44 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/02 03:18:46 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "../environnement/env.h"
#include "execute.h"

int	handle_env(int flag_env, char *cmd, char *path_cmd, int flag)
{
	if (cmd && cmd[0] == '\0')
	{
		if (flag_env == 0)
		{
			if (flag)
				return (ft_error(NULL, "command not found"));
			return (127);
		}
		else
			free(path_cmd);
		return (0);
	}
	return (1);
}

int	execute_simple_cmd(t_env **env, t_cmd_node *cmd)
{
	char	*path_cmd;

	if (cmd->executable == NULL)
		return (0);
	if (is_builtin(cmd))
		return (execute_builtin(env, cmd));
	path_cmd = get_path_cmd(*env, cmd);
	if (!path_cmd)
	{
		if (!handle_env(cmd->flag_env, cmd->executable, path_cmd, 0)
			|| handle_env(cmd->flag_env, cmd->executable, path_cmd, 0) == 127)
			return (handle_env(cmd->flag_env, cmd->executable, path_cmd, 1));
		if (cmd->executable && cmd->flag_env == 1 && cmd->type_qoutes == -1)
		{
			free_str_list(cmd->arguments);
			cmd->arguments = ft_split(cmd->executable, ' ');
			free(cmd->executable);
			cmd->executable = ft_strdup(cmd->arguments[0]);
			path_cmd = get_path_cmd(*env, cmd);
		}
		if (!path_cmd)
			return (handle_null_path(env, cmd));
	}
	return (run_cmd(env, path_cmd, cmd));
}

int	execute_redir(t_env **env, t_redir_node *cmd)
{
	int				fd_in;
	int				fd_out;
	t_redir_node	*tmp;

	fd_in = dup(0);
	fd_out = dup(1);
	while (cmd)
	{
		if (cmd->redir_type == IN || cmd->redir_type == OUT
			|| cmd->redir_type == APPEND)
		{
			if (util_redir(cmd, cmd->redir_type, fd_in, fd_out))
				return (1);
		}
		tmp = cmd;
		cmd = cmd->next;
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
	execute_simple_cmd(env, tmp->cmd);
	return (0);
}

int	util_redir(t_redir_node *cmd, t_redir_type type, int fd_in, int fd_out)
{
	int	fd_file;

	if (type == IN)
		fd_file = open(cmd->filename, O_RDONLY);
	else if (type == OUT)
		fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_file == -1)
	{
		ft_error(cmd->filename, "No such file or directory");
		return (127);
	}
	if (type == IN)
		dup2(fd_file, fd_in);
	else
		dup2(fd_file, fd_out);
	close(fd_file);
	return (0);
}
