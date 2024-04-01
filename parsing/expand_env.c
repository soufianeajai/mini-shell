#include "../environnement/env.h"
#include "parsing.h"
#include <fcntl.h>

void	expand_env(t_token **token, t_env *env_list)
{
	t_token	*temp;
	char	*value;
	char	**temp_str;

	temp = *token;
	while (temp)
	{
		if (temp->type == ENV)
		{
			temp_str = &temp->str;
			value = get_env_value(temp->str, env_list);
			ft_free(temp_str);
			if (value && *value == '\0')
				ft_free(&value);
			else
				temp->str = value;
			temp->type = CMD;
		}
		temp = temp->next;
	}
}


char	*handle_expandable(char **input, t_env *env_list)
{
	char	*key;
	char	*value;

	key = 0;
	value = 0;
	if (**input == '$' && isalpha_num(**(input + 1)))
	{
		if (is_alpha(**(input + 1)))
		{
			(*input)++;
			key = get_value(input, 1);
			value = ft_getenv(env_list, key);
			ft_free(&key);
		}
		else
		{
			*input = *(input + 2);
			value = get_value(input, 0);
		}
	}
	return (value);
}
char	*get_env_value(char *input, t_env *env_list)
{
	char	*result;
	char	*value;

	result = NULL;
	value = NULL;
	while (input && *input)
	{
		if (*input == '$' && isalpha_num(*(input + 1)))
			value = handle_expandable(&input, env_list);
		else if (*input == '$' && *(input + 1) == '?')
		{
			value = ft_itoa(EXIT_CODE);
			input = input + 2;
		}
		else if (*input == '$')
		{
			input++;
			value = ft_strjoin("$", get_value(&input, 0), 2);
		}
		else
			value = get_value(&input, 0);
		result = ft_strjoin(result, value, 3);
	}
	return (result);
}

char	*get_value(char **str, int flag)
{
	char	*start;
	char	*value;
	char	temp;

	start = *str;
	value = 0;
	if (flag)
	{
		while (**str && isalpha_num(**str))
			(*str)++;
	}
	else
	{
		while (**str && **str != '$')
			(*str)++;
	}
	temp = **str;
	**str = '\0';
	value = ft_strdup(start);
	**str = temp;
	return (value);
}
