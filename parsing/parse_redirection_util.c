/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:53:53 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:53:54 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ignore(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_exitcode = 130;
}

void	sig_quit(void)
{
	ft_putstr_fd("^\\Quit: 3\n", 2);
	g_exitcode = 131;
}

void	check_her_doc(t_token **token, t_env *env_list)
{
	char	*input;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open(".her_doc.c", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(0);
		if (!input || ft_strcmp(input, (*token)->str) == 0)
		{
			ft_free(&input);
			break ;
		}
		if (*token && (*token)->type_qoutes == -1)
			input = get_expandable(input, env_list);
		write(fd, ft_strjoin(input, "\n", 0), ft_strlen(input) + 1);
		free(input);
	}
	close(fd);
	exit(0);
}

t_redir_node	*create_redir_node(t_redir_type type)
{
	t_redir_node	*node;

	node = malloc(sizeof(t_redir_node));
	if (!node)
		return (0);
	node->cmd = 0;
	node->filename = 0;
	node->type = REDIR;
	node->next = 0;
	node->redir_type = type;
	return (node);
}

int	check_code(void)
{
	if (g_exitcode == 130)
	{
		g_exitcode = 1;
		return (0);
	}
	return (1);
}
