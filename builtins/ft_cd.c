/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:25:07 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/30 23:25:09 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	utils_cd(char *path, t_env **env, char *oldpwd)
{
	char	*pwd;

	if (chdir(path) == -1)
	{
		free(oldpwd);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		set_env_value(env, "OLDPWD", oldpwd);
		set_env_value(env, "PWD", pwd);
		free(pwd);
		free(oldpwd);
	}
	else
	{
		free(oldpwd);
		ft_putstr_fd("cd: cannot access parent directories", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_env **env, t_cmd_node *cmd)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (cmd->arguments[1] == NULL)
	{
		path = ft_getenv(*env, "HOME");
		if (!path)
		{
			free(oldpwd);
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = cmd->arguments[1];
	if (utils_cd(path, env, oldpwd))
		return (1);
	return (0);
}
