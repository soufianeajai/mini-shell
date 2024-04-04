/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:50:33 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:50:36 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environnement/env.h"
#include "parsing.h"
#include <fcntl.h>

void	consume(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
}

t_pipe_node	*create_pipe_node(t_tree_node *left, t_tree_node *right)
{
	t_pipe_node	*node;

	node = malloc(sizeof(t_pipe_node));
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return (node);
}

t_tree_node	*add_to_tree(void *node, t_node_type type)
{
	t_tree_node	*ret_node;

	ret_node = malloc(sizeof(t_tree_node));
	ret_node->type = type;
	ret_node->node = node;
	return (ret_node);
}

void	ft_lstadd_back_redir(t_redir_node **head, t_redir_node *new)
{
	t_redir_node	*tmp;

	if (new)
	{
		if (!head)
			head = &new;
		else
		{
			tmp = *head;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = new;
		}
	}
}

t_cmd_node	*create_cmd_node(char *executable, char **arguments, int flag_env,
		int flag_quote)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	node->type = CMD;
	node->executable = executable;
	node->arguments = arguments;
	node->flag_env = flag_env;
	node->type_qoutes = flag_quote;
	return (node);
}
