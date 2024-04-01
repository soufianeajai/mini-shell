#include "parsing.h"
#include "../environnement/env.h"
#include <fcntl.h>

void ignore(int sig)
{
	(void)sig;
}
void	check_her_doc (t_token **token, t_env *env_list)
{
	t_redir_node *redir;
	char *input;
	int fd;
	char *filename;

	signal(SIGINT,SIG_DFL);
	filename = ft_strdup(".her_doc.c");
	redir = (t_redir_node *)(*token);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if(!input || strcmp(input, redir->filename) == 0) 
		{
			free(input);
			input = NULL;
			break;
		}
		if (*token && (*token)->type_qoutes == -1)
			input = get_env_value(input, env_list);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		ft_free(&input);
	}
	free(redir->filename);
	close(fd);
}

int is_special_char(char *c)
{
	if (c)
	{
		if (*c == '>' || *c == '<' || *c == '|')
			return (1);
	}
	return (0);
}
t_redir_node	*parse_redirection(t_token **tokens, t_env *env_list)
{
	t_redir_node	*node;
	redir_type		type;
	char			*filename;
	int				nbr_here_doc = 0;

	if ((*tokens) && (*tokens)->type == REDIR)
	{
		node = malloc(sizeof(t_redir_node));
		node->cmd = 0;
		node->filename = 0;
		node->type = REDIR;
		node->next = 0;
		node->redir_type = get_redir_type(tokens);
		// need to add expand to her_doc
		if (node->redir_type == HER_DOC)
		{
			if ((*tokens)->next && is_special_char((*tokens)->next->str))
				return(NULL);
			else if (((*tokens)->next))
			{
				signal(SIGINT,SIG_IGN);
				consume(tokens);
				int pid = fork();
				if (pid == 0)
				{
					check_her_doc(tokens, env_list);
					exit(0);
				}
				else
				{
					signal(SIGINT, ignore);
					node->filename = ft_strdup(".her_doc.c");
					node->redir_type = IN;
					waitpid(pid, NULL, 0);
				}
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
	else
		node = 0;	
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
