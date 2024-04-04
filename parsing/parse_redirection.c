/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:49:57 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:49:58 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environnement/env.h"
#include "parsing.h"

t_redir_node	*handle_herdoc(t_token **tokens, t_env *env_list,
		t_redir_node **redir_node, int *flag_redir)
{
	int	pid;
	int	status;

	if ((*tokens)->next && is_special_char((*tokens)->next->str, flag_redir))
		return (0);
	else if (((*tokens)->next))
	{
		signal(SIGINT, SIG_IGN);
		consume(tokens);
		pid = fork();
		if (pid == 0)
			check_her_doc(tokens, env_list);
		else
		{
			signal(SIGINT, ignore);
			waitpid(pid, &status, 0);
			if (!check_code())
				return (0);
			EXIT_CODE = WEXITSTATUS(status);
			(*redir_node)->filename = ft_strdup(".her_doc.c");
			(*redir_node)->redir_type = IN;
		}
	}
	return (*redir_node);
}

t_redir_node	*parse_redirection(t_token **tokens, t_env *env_list,
		int *flag_redir)
{
	t_redir_node	*node;

	node = 0;
	if ((*tokens) && (*tokens)->type == REDIR)
	{
		node = create_redir_node(get_redir_type(tokens));
		if (node->redir_type == HER_DOC)
		{
			if (!handle_herdoc(tokens, env_list, &node, flag_redir))
			{
				free_redir_node(node);
				return (0);
			}
		}
		else
		{
			consume(tokens);
			if (*tokens)
				node->filename = ft_strdup((*tokens)->str);
		}
		consume(tokens);
	}
	return (node);
}

t_redir_type	get_redir_type(t_token **tokens)
{
	t_redir_type	type;

	if (!ft_strncmp((*tokens)->str, "<", 1))
		type = IN;
	if (!ft_strncmp((*tokens)->str, ">", 1))
		type = OUT;
	if (!ft_strncmp((*tokens)->str, ">>", 2))
		type = APPEND;
	if (!ft_strncmp((*tokens)->str, "<<", 2))
		type = HER_DOC;
	return (type);
}
