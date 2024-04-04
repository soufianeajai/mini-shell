/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:22:59 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:23:00 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"
#include "env.h"

char	*ft_getenv(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->key)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_path(t_cmd_node *cmd)
{
	if (access(cmd->executable, X_OK) == 0 && (ft_strncmp(cmd->executable, "./",
				2) == 0 || ft_strncmp(cmd->executable, "/", 1) == 0))
		return (1);
	return (0);
}

char	*get_path_cmd(t_env *env, t_cmd_node *cmd)
{
	char	**path;
	int		i;
	char	*path_cmd;
	char	*util;

	i = 0;
	if (is_path(cmd))
		return (cmd->executable);
	path = ft_split(ft_getenv(env, "PATH"), ':');
	while (path && path[i] && cmd->executable && cmd->executable[0] != '/'
		&& cmd->executable[0] != '.')
	{
		util = ft_strjoin(path[i++], "/", 0);
		path_cmd = ft_strjoin(util, cmd->executable, 0);
		if (access(path_cmd, X_OK) == 0 && cmd->executable[0] != '\0')
		{
			free(util);
			free_str_list(path);
			return (path_cmd);
		}
		free(util);
		free(path_cmd);
		path_cmd = NULL;
	}
	return ((char *)free_str_list(path));
}
