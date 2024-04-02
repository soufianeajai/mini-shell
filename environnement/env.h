/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:13:34 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/02 03:13:36 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../parsing/parsing.h"

void	ft_lstadd_back_env(t_env **lst, int index, char *str);
void	env_copy(t_env **env, char **environ);
char	*ft_getenv(t_env *env, char *key);
void	set_env_value(t_env **env, char *key, char *value);
char	*get_path_cmd(t_env *env, t_cmd_node *cmd);
void	free_env_list(t_env **env_list);

#endif
