#include "../environnement/env.h"
#include "parsing.h"
#include <fcntl.h>

void	ignore(int sig)
{
	EXIT_CODE = 130;
	(void)sig;
}
void	check_her_doc(t_token **token, t_env *env_list)
{
	t_redir_node	*redir;
	char			*input;
	int				fd;
	char			*filename;

	signal(SIGINT, SIG_DFL);
	filename = ft_strdup(".her_doc.c");
	redir = (t_redir_node *)(*token);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if(!input)
			exit(0);
		if (!input || strcmp(input, redir->filename) == 0)
		{
			ft_free(&input);
			break ;
		}
		if (*token && (*token)->type_qoutes == -1)
			input = get_env_value(input, env_list);
		write(fd, ft_strjoin(input, "\n", 0), ft_strlen(input) + 1);
		ft_free(&input);
	}
	free(redir->filename);
	close(fd);
	exit(0);
}

t_redir_node	*create_redir_node(redir_type type)
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

t_redir_node	*handle_herdoc(t_token **tokens, t_env *env_list,
		t_redir_node **redir_node, int *flag_redir)
{
	t_redir_node	*node;
	int				pid;
	int				status;

	node = *redir_node;
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
			if(EXIT_CODE == 130)
			{	
				EXIT_CODE = 1;
				return (0);
			}
			EXIT_CODE = WEXITSTATUS(status);
			node->filename = ft_strdup(".her_doc.c");
			node->redir_type = IN;
		}
	}
	return (*redir_node);
}

t_redir_node	*parse_redirection(t_token **tokens, t_env *env_list, int *flag_redir)
{
	t_redir_node	*node;
	redir_type		type;
	char			*filename;

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

redir_type	get_redir_type(t_token **tokens)
{
	redir_type	type;

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
