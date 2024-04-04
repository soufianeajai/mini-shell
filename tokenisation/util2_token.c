/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:01:03 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 18:01:05 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handling_qoutes_util(int *i, int *flag, t_token *tmp)
{
	if (tmp->str[*i] && *flag == is_qoutes(tmp->str[*i], &tmp))
	{
		*i = *i + 1;
		*flag = 0;
	}
}

t_token	*create_node(int len, t_node_type type, int index)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->len = len;
	new->type = type;
	if (type == ENV)
		new->flag_env = 1;
	else
		new->flag_env = 0;
	new->type_qoutes = -1;
	new->index = index;
	new->next = NULL;
	new->prev = NULL;
	new->str_qoutes = NULL;
	return (new);
}

void	ft_lstadd_back(t_token **lst, int len, t_node_type type, int index)
{
	t_token	*new;
	t_token	*p;

	new = create_node(len, type, index);
	if (!new)
		return ;
	p = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (p->next)
			p = p->next;
		new->prev = p;
		p->next = new;
	}
}
