#include "parsing.h"
#include "../environnement/env.h"

char	*parse_exec(t_token **tokens, char *executable, int *flag_env)
{
	char	*exec;

	exec = 0;
	if (!executable)
	{
		*flag_env = (*tokens)->flag_env;
		exec = ft_strdup((*tokens)->str);
		consume(tokens);
	}
	if (!exec)
		return (executable);
	return (exec);
}
int	is_special_char(char *c, int *flag_redir)
{
	if (c)
	{
		if (*c == '>' || *c == '<' || *c == '|')
		{
			*flag_redir = 1;
			return (1);
		}
	}
	return (0);
}
int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	isalpha_num(char c)
{
	if (is_alpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}