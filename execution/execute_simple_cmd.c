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
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int	ft_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	if (!ft_strcmp(error, "command not found") || !ft_strcmp(error,
			"No such file or directory"))
		return (127);
	return (126);
}

int	check_type(int flag, char *path, struct stat path_stat, char *cmd)
{
	if (S_ISDIR(path_stat.st_mode))
	{
		if (flag)
			ft_error((char *)path, "is a directory");
		return (126);
	}
	if (S_ISREG(path_stat.st_mode) && (ft_strchr(cmd, '/') || (!ft_strchr(cmd,
					'/') && cmd[0] == '/')) && cmd[0] != '.')
	{
		if (flag)
			ft_error(cmd, "No such file or directory");
		return (127);
	}
	else if (S_ISREG(path_stat.st_mode) && access(cmd, X_OK) == -1)
	{
		if (flag)
			ft_error(cmd, "Permission denied");
		return (126);
	}
	return (0);
}
int	check_path(char *path, char *cmd, int flag)
{
	struct stat	path_stat;
	//printf("path: %s %s\n", path,cmd);
	if (stat(path, &path_stat) == -1 && (ft_strchr(cmd, '/') || (!ft_strchr(cmd,
					'/') && cmd[0] == '/')))
	{
		if (flag)
		{
			if (errno == ENOTDIR)
				return (ft_error(cmd, "Not a directory"));
			else
				return (ft_error(cmd, "No such file or directory"));
		}
		return (1);
	}
	return (check_type(flag, (char *)path, path_stat, cmd));
}

char	**lst_to_arr(t_env *env)
{
	int		i;
	t_env	*curr;
	char	**arr;

	i = 0;
	curr = env;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->key, "=", 0);
		arr[i] = ft_strjoin(arr[i], env->value, 0);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

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
int	handle_env(int flag_env, char *cmd, char *path_cmd)
{
	//printf("flag_env: %d cmd :  -%p-\n", flag_env,cmd);
	if (cmd && cmd[0] == '\0')
	{
		if (flag_env == 0)
			return (ft_error(NULL, "command not found"));
		else
			free(path_cmd);
		return (0);
	}
	return (1);
}

int	execute_simple_cmd(t_env **env, t_cmd_node *cmd)
{
	char	*path_cmd;

//	signal(SIGINT, SIG_DFL);
	if (cmd->executable == NULL)
		return (0);
	if (is_builtin(cmd))
		return (execute_builtin(env, cmd));
	path_cmd = get_path_cmd(*env, cmd);
	if (!path_cmd)
	{
		if (!handle_env(cmd->flag_env, cmd->executable, path_cmd) || handle_env(cmd->flag_env, cmd->executable, path_cmd) == 127)
			return (handle_env(cmd->flag_env, cmd->executable, path_cmd));
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

//	signal(SIGINT, SIG_DFL);
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
