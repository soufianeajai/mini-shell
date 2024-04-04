/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:55:50 by sajaite           #+#    #+#             */
/*   Updated: 2024/04/04 21:55:52 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtin.h"
#include "execution/execute.h"
#include "minishell.h"

int	len_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	check_valid_identifier1(char *arg)
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
		if ((!is_alpha(arg[i]) && arg[i] != '_'))
			return (1);
		i++;
	}
	if (arg[0] == '=' || (arg[i] == '=' && ft_isspace(arg[i - 1])
			&& ft_isspace(arg[i + 1])))
		return (1);
	return (0);
}

char	*get_last_arg(char **arguments, int flag)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = 0;
	if (!arguments)
		return (0);
	if (!flag)
	{
		while (arguments[i])
			i++;
		if (i)
			cmd = ft_strdup(arguments[i - 1]);
	}
	else
	{
		if (arguments[1] && ft_strchr(arguments[1], '=') != 0
			&& !check_valid_identifier1(arguments[1]))
			cmd = ft_substr(arguments[1], 0, len_equal(arguments[1]));
		else if (arguments[1])
			cmd = ft_strdup(arguments[1]);
		else
			cmd = ft_strdup(arguments[0]);
	}
	return (cmd);
}

t_cmd_node	*get_cmd_node(t_redir_node *redir)
{
	t_redir_node	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
	}
	return (tmp->cmd);
}

char	*get_node(t_tree_node *tree)
{
	char		*cmd;
	t_cmd_node	*cmd_node;

	cmd = 0;
	if (tree && (tree->type == CMD || tree->type == REDIR))
	{
		if (tree->type == CMD)
			cmd_node = (t_cmd_node *)tree->node;
		else
			cmd_node = get_cmd_node(((t_redir_node *)tree->node));
		if (cmd_node && cmd_node->executable && !(cmd_node->arguments))
			cmd = ft_strdup(cmd_node->executable);
		else if (cmd_node && ft_strcmp(cmd_node->executable, "export")
			&& cmd_node->arguments)
			cmd = get_last_arg(cmd_node->arguments, 0);
		else if (cmd_node && cmd_node->arguments)
			cmd = get_last_arg(cmd_node->arguments, 1);
	}
	return (cmd);
}

// char	*get_node(t_tree_node *tree)
// {
// 	char *cmd;
// 	t_cmd_node *cmd_node;

// 	cmd = 0;
// 	if (tree && tree->type == CMD)
// 	{
// 		cmd_node = (t_cmd_node *)tree->node;
// 		if (cmd_node && cmd_node->executable && !(cmd_node->arguments))
// 			cmd = ft_strdup(cmd_node->executable);
// 		else if (cmd_node && ft_strcmp(cmd_node->executable, "export")
// 			&& cmd_node->arguments)
// 			cmd = get_last_arg(cmd_node->arguments, 0);
// 		else if (cmd_node && cmd_node->arguments)
// 			cmd = get_last_arg(cmd_node->arguments, 1);
// 	}
// 	if (tree && tree->type == REDIR)
// 	{
// 		cmd_node = get_cmd_node(((t_redir_node *)tree->node));
// 		if (cmd_node && cmd_node->executable && !(cmd_node->arguments))
// 			cmd = ft_strdup(cmd_node->executable);
// 		else if (cmd_node && ft_strcmp(cmd_node->executable, "export")
// 			&& cmd_node->arguments)
// 			cmd = get_last_arg(cmd_node->arguments, 0);
// 		else if (cmd_node && cmd_node->arguments)
// 			cmd = get_last_arg(cmd_node->arguments, 1);
// 	}
// 	return (cmd);
// }
