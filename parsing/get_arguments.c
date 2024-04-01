#include "../environnement/env.h"
#include "parsing.h"
#include <fcntl.h>

char	**get_arguments(char *exec, char **arguments, t_token **tokens)
{
	char	**args;
	int		len_args;
	int		i;
	int		len;

	i = 0;
	len = count_len(arguments);
	len_args = count_args(*tokens) + len;
	if (!(args = malloc(sizeof(char *) * (len_args + 2))))
		return (0);
	args[0] = ft_strdup(exec);
	while (++i < len)
		args[i] = ft_strdup(arguments[i]);
	while (i < len_args && (*tokens)->str)
	{
		args[i] = ft_strdup((*tokens)->str);
		i++;
		consume(tokens);
	}
	if (i < len_args)
		consume(tokens);
	args[i] = 0;
	free_str_list(arguments);
	return (args);
}

int	count_len(char **arguments)
{
	int	len;

	len = 0;
	if (arguments && *arguments)
	{
		while (arguments[len])
			len++;
	}
	return (len);
}

int	count_args(t_token *tokens)
{
	int	len_args;

	len_args = 0;
	while (tokens && tokens->type == CMD)
	{
		len_args++;
		tokens = tokens->next;
	}
	return (len_args);
}
