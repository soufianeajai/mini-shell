/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:13:40 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/02 03:13:42 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"
#include "env.h"

static t_env	*alloc_node_env(char *key, char *value, int flag)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void	set_env_value(t_env **env, char *key, char *value, int flag)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp && tmp->key)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = alloc_node_env(key, value, flag);
	tmp = *env;
	if (!*env)
		*env = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_env_list(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		*env_list = (*env_list)->next;
		ft_free(&(temp->key));
		ft_free(&(temp->value));
		free(temp);
		temp = *env_list;
	}
}
