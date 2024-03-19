#include "../minishell.h"
#include "../parsing/parsing.h"
#include "env.h"

char *ft_getenv(t_env *env, char *key)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp && tmp->key)
	{
		if (ft_strncmp(tmp->key,key,ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int is_path( t_cmd_node *cmd)
{
	if (access(cmd->executable, X_OK) == 0)
		return (1);
	return (0);
}

char *get_path_cmd(t_env *env, t_cmd_node *cmd)
{
	char **path;
	int i;
	char *path_cmd;
	char *util;

	i = 0;
	// /bin + / =  /bin/  + ls = /bin/ls
	if (is_path(cmd))
		return (cmd->executable);
	path = ft_split(ft_getenv(env, "PATH"), ':');
	while (path[i] && cmd->executable)
	{
		util = ft_strjoin(path[i++], "/");
		path_cmd = ft_strjoin(util, cmd->executable);
		if (access(path_cmd, X_OK) == 0)
		{
			free(util);
			ft_free(path);
			return (path_cmd);
		}
		free(util);
		free(path_cmd);
		path_cmd = NULL;
	}
	ft_free(path);
	return (NULL);
}
