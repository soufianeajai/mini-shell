/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_smp_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:29:11 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:29:15 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
