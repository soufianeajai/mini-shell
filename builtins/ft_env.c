/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:34:10 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/30 23:34:11 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_error_export(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}


void print_export(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	while (tmp)
	{
		if (tmp->key && (tmp->flag == 1 || tmp->flag == 2))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			if (tmp->value && tmp->value[0] != '\0')
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd("\n", 1);
			}
			else
				ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

int	ft_env(t_env *env, int type)
{
	t_env	*tmp;

	//type 0 ->  env, type 1 -> export
	tmp = env;

	if (type == 1)
	{
		print_export(env);
		return (0);
	}
	while (tmp)
	{
		if (tmp->key && tmp->value && (tmp->flag == 1 || tmp->flag == 0))
		{
			ft_putstr_fd(tmp->key, 1);
				ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
