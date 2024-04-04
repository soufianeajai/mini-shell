/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:51:03 by sajaite           #+#    #+#             */
/*   Updated: 2024/04/04 21:51:04 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtin.h"
#include "execution/execute.h"
#include "minishell.h"

void	update_underscore_var(t_env **env_list, t_tree_node *node)
{
	t_env	*temp;
	char	*cmd;

	if (node == NULL)
		return ;
	cmd = get_node(node);
	temp = *env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, "_", 2) == 0)
		{
			free(temp->value);
			temp->value = cmd;
			break ;
		}
		temp = temp->next;
	}
}

void	run_command(t_tree_node *tree, t_env **env_list, t_token **tokens,
		char *input)
{
	if (tree)
	{
		update_underscore_var(env_list, tree);
		if (tree->type == CMD)
			exec_cmd(tree, env_list);
		else if (tree->type == REDIR)
			exec_redir(tree, env_list);
		else
			execute(tree, env_list);
	}
	free_tree(tree);
	free_tokens(tokens);
	free(input);
}

char	*get_input(t_env **env_list)
{
	char	*input;

	input = 0;
	handle_signals();
	input = readline("➜  MiNiSh ✗ ");
	if (!input)
	{
		free_env_list(env_list);
		exit(g_exitcode);
	}
	return (input);
}

void	init_data(int ac, char **av)
{
	(void)ac;
	(void)av;
	g_exitcode = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*tokens;
	t_env	*env_list;
	t_token	*temp_tokens;

	init_data(ac, av);
	env_list = 0;
	env_copy(&env_list, env);
	while (1)
	{
		tokens = 0;
		input = get_input(&env_list);
		if (ft_strlen(input) > 0)
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		tokenisation(&tokens, input);
		handling_qoutes(&tokens);
		temp_tokens = tokens;
		run_command(parse_command(&tokens, env_list), &env_list, &temp_tokens,
			input);
	}
}
