#include "parsing.h"
#include "../environnement/env.h"
#include <fcntl.h>

void	expand_env(t_token **token, t_env *env_list)
{
	t_token *temp;

	temp = *token;
	while (temp)
	{
		if (temp->type == ENV)
		{
			temp->str = get_env_value(temp->str, env_list);
			if (temp->str && *temp->str == '\0')
			{
				free(temp->str);
				temp->str = NULL;
			}
			temp->type = CMD;
		}
		temp = temp->next;
	}
}

// this case not working echo gggg+++$USER$USER$++
char	*get_env_value(char *str, t_env *env_list)
{
	t_env	*env;
	char	*key;
	char	*expanded_value;

	env = env_list;
	expanded_value = get_value_before(str);
	while (*str && *str != '$')
		str++;
	while (*str)
	{
		if (*str == '$' && *(str + 1))
		{
			str++;
			if (isalpha_num(*str))
			{
				key = get_key(str);
				while (*str && *str != '$' && isalpha_num(*str))
					str++;
				expanded_value = ft_strjoin(expanded_value, ft_getenv(env_list, key));
			}
			else
			{
				expanded_value = ft_strjoin(expanded_value, get_value_before(str));	
				while (*str && *str != '$')
					str++;
			}
		}
		else if (*str == '$')
		{
			expanded_value = ft_strjoin(expanded_value, "$");
			str++;
		}
		else
		{
			expanded_value = ft_strjoin(expanded_value, get_value_before(str));
			while (*str && *str != '$')
				str++;
		}
	}
	return (expanded_value);
}
int isalpha_num(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}
char *get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '$' && isalpha_num(str[i]))
		i++;
	key = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '$' && isalpha_num(str[i]))
	{	
		key[i] = str[i];
		i++;
	}
	key[i] = 0;
	return (key);
}
char	*get_value_before(char *str)
{
	int		i;
	char	*value;
	int len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '$')
		len++;
	value = malloc(len + 1);
	while (i < len)
	{
		value[i] = str[i];
	//	str++;
		i++;
	}
	value[i] = 0;
	return (value);
}