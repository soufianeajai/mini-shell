#include "../environnement/env.h"
#include "parsing.h"

t_tree_node	*parse_command(t_token **tokens, t_env *env_list)
{
	t_tree_node	*tree;
	int			syntax_error;

	syntax_error = check_syntax(*tokens);
	expand_env(tokens, env_list);
	tree = parse_pipeline(tokens, env_list);
	if (syntax_error)
	{
		free_tree(tree);
		return (0);
	}
	return (tree);
}

t_tree_node	*parse_pipeline(t_token **tokens, t_env *env_list)
{
	t_pipe_node	*pipe_node;
	t_tree_node	*tree_node;
	t_tree_node	*left;
	t_tree_node	*right;
	int			redir_syntax;

	pipe_node = 0;
	tree_node = 0;
	redir_syntax = 0;
	left = parse_simple_command(tokens, env_list, &redir_syntax);
	if (!left)
		return (0);
	if (*tokens && (*tokens)->type == PIPE)
	{
		consume(tokens);
		right = parse_pipeline(tokens, env_list);
		pipe_node = create_pipe_node(left, right);
		tree_node = add_to_tree((void *)pipe_node, PIPE);
		return (tree_node);
	}
	return (left);
}
t_tree_node	*combine_cmd(t_cmd_node *cmd, t_redir_node *head)
{
	t_tree_node		*node;
	t_redir_node	*redir;

	node = 0;
	redir = head;
	if (head)
	{
		while (redir->next)
			redir = redir->next;
		redir->cmd = cmd;
		node = add_to_tree((void *)(head), REDIR);
	}
	else
		node = add_to_tree((void *)cmd, CMD);
	return (node);
}
t_redir_node	*parse_redir(t_token **tokens, t_redir_node **head_redir,
		t_env *env_list, int *flag_redir)
{
	t_redir_node	*redir_node;

	redir_node = 0;
	while ((*tokens) && (*tokens)->type == REDIR)
	{
		redir_node = parse_redirection(tokens, env_list, flag_redir);
		if (!redir_node)
			return (0);
		if (!(*head_redir) && redir_node)
			*head_redir = redir_node;
		else
			ft_lstadd_back_redir(head_redir, redir_node);
	}
	return (redir_node);
}

t_tree_node	*parse_simple_command(t_token **tokens, t_env *env_list,
		int *flag_redir)
{
	t_redir_node	*head_redir;
	char			*executable;
	char			**arguments;
	int				flag_env;

	executable = 0;
	arguments = 0;
	head_redir = 0;
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == CMD)
		{
			executable = parse_exec(tokens, executable, &flag_env);
			arguments = get_arguments(executable, arguments, tokens);
		}
		else
		{
			if (!parse_redir(tokens, &head_redir, env_list, flag_redir)
				|| *flag_redir)
				return ((t_tree_node *)free_tree_util(executable, arguments,
						flag_env, head_redir));
		}
	}
	return (combine_cmd(create_cmd_node(executable, arguments, flag_env),
			head_redir));
}
