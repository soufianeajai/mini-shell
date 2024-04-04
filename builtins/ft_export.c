/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:37:12 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/31 00:37:15 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=' && i != 0)
		{
			i++;
			continue ;
		}
		if ((!isalpha_num(arg[i]) && arg[i] != '_'))
			return (print_error_export(arg));
		i++;
	}
	if (arg[0] == '=' || (arg[i] == '=' && ft_isspace(arg[i - 1])
			&& ft_isspace(arg[i + 1])))
		return (print_error_export(arg));
	return (0);
}

void	add_to_env(int append, t_env **env, char *key, char *value)
{
	char	*oldvalue;
	char	*tmp;

	oldvalue = ft_getenv(*env, key);
	if (append == 1)
	{
		value++;
		if (oldvalue)
		{
			tmp = ft_strjoin(oldvalue, value, 0);
			value = tmp;
		}
		append = 0;
	}
	if (append == 0)
	{
		if (oldvalue)
			remove_env(env, key);
		set_env_value(env, key, value);
	}
}

void	handle_key_value(char *arg, t_env **env)
{
	int		index;
	char	*key;
	char	*value;
	int		append;

	append = 0;
	index = ft_strchr(arg, '=');
	if (arg[index - 1] == '+')
	{
		append = 1;
		index--;
	}
	key = ft_substr(arg, 0, index);
	value = ft_substr(arg, index + 1, ft_strlen(arg) - index - 1);
	add_to_env(append, env, key, value);
	free(key);
	free(value);
}

int	handling_args(char **arg, t_env **env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (arg[i])
	{
		if (check_valid_identifier(arg[i]))
		{
			flag = 1;
			i++;
			continue ;
		}
		if (ft_strchr(arg[i], '=') == 0 && arg[i][0] != '=')
		{
			i++;
			continue ;
		}
		handle_key_value(arg[i], env);
		i++;
	}
	return (flag);
}
void add_env(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env *get_element(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = ft_strjoin("declare -x ", ft_strdup(key), 2);
	new->value = ft_strdup(value);
	new->next = 0;
	return (new);
}

t_env	**copy_env(t_env **env)
{
	t_env	**export;
	t_env	*temp;
//	t_env	*new;
	int		oldpwd_flag;

	oldpwd_flag = 0;
	export = malloc(sizeof(t_env *));
	if (!export)
		return (0);
	*export = 0;
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "_") == 0)
		{
			temp = temp->next;
			continue ;
		}
		if (ft_strcmp(temp->key, "OLDPWD") == 0)
			oldpwd_flag = 1;
		add_env(export, get_element(temp->key, temp->value));
		temp = temp->next;
	}
	if (!oldpwd_flag)
	{
	//	new = get_element("OLDPWD", "");
		add_env(export, get_element("OLDPWD", ""));
	}
	return (export);
}

int	ft_export(t_env **env, t_cmd_node *cmd)
{
	int	i;
	t_env	**export;
	i = 1;
	
	if (cmd && cmd->arguments && cmd->arguments[1] == NULL)
	{
		export = copy_env(env);
		ft_env(*export);
		free_env_list(export);
		return (0);
	}
	return (handling_args(cmd->arguments, env));
}
