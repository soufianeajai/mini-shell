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
			value = get_env_value(temp->str, env_list, temp->str_qoutes);
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
	if (**input == '$' && isalpha_num(*((*input) + 1)))
	{
		if (is_alpha(*((*input) + 1)))
		{
			(*input)++;
			key = get_value(input, 1);
			value = ft_getenv(env_list, key);
			ft_free(&key);
		}
		else
		{
			*input = (*input + 2);
			value = get_value(input, 0);
		}
	}
	return (value);
}
int	look_for_dollar(char *tab_qoutes, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (tab_qoutes[i] == '$')
			return (1);
		i++;
		j++;
	}
	return (0);
}

int	check_qts(char *tab_qoutes, int i, int type, int *len)
{
	int	start;

	i++;
	start = i;
	*len = 0;
	while (tab_qoutes[i])
	{
		if (type == 1 && tab_qoutes[i] == '\'')
			break ;
		if (type == 2 && tab_qoutes[i] == '\"')
			break ;
		*len = *len + 1;
		i++;
	}
	if (len)
		return (look_for_dollar(tab_qoutes, start, *len));
	return (0);
}

int	skip_2(int flag_dollar, int len_pair, int *i)
{
	if (len_pair == 0 && flag_dollar == 0)
		*i = *i + 1;
	else if (flag_dollar == 0)
		*i = len_pair + 1;
	else
		return (1);
	return (0);
}

void	skip(char *tab_qoutes, int *i)
{
	int	len_pair;
	int	flag_dollar;

	while (tab_qoutes[*i])
	{
		if (tab_qoutes[*i] == '$')
			return ;
		if (tab_qoutes[*i] == '\'')
		{
			flag_dollar = check_qts(tab_qoutes, *i, 1, &len_pair);
			if (skip_2(flag_dollar, len_pair, i))
				return ;
		}
		if (tab_qoutes[*i] == '\"')
		{
			flag_dollar = check_qts(tab_qoutes, *i, 2, &len_pair);
			if (skip_2(flag_dollar, len_pair, i))
				return ;
		}
		*i = *i + 1;
	}
	return ;
}
void	get_next(char *tab_qoutes, int *i, int type)
{
	*i = *i + 1;
	if (type == 1)
	{
		while (tab_qoutes[*i] && tab_qoutes[*i] != '\'')
			*i = *i + 1;
		if (tab_qoutes[*i] && tab_qoutes[*i] == '\'')
			*i = *i + 1;
	}
	else
	{
		while (tab_qoutes[*i] && tab_qoutes[*i] != '\"')
			*i = *i + 1;
		if (tab_qoutes[*i] && tab_qoutes[*i] == '\"')
			*i = *i + 1;
	}
}

int	checkfor_qoutes(char *tab_qoutes, int *i)
{
	while (tab_qoutes[*i])
	{
		skip(tab_qoutes, i);
		if (tab_qoutes[*i] && tab_qoutes[*i] == '\'')
		{
			get_next(tab_qoutes, i, 1);
			return (0);
		}
		else if (tab_qoutes[*i] && tab_qoutes[*i] == '\"')
		{
			get_next(tab_qoutes, i, 2);
			return (1);
		}
		else
		{
			*i = *i + 1;
			return (1);
		}
	}
	return (1);
}

char	*handle_dollar(char **input)
{
	(*input)++;
	return (ft_strjoin("$", get_value(input, 0), 2));
}
char	*get_env_value(char *input, t_env *env_list, char *tab_qoutes)
{
	char	*result;
	char	*value;
	int		i;

	i = 0;
	result = NULL;
	value = NULL;
	while (input && *input)
	{
		if (*input == '$' && isalpha_num(*(input + 1))
			&& checkfor_qoutes(tab_qoutes, &i))
			value = handle_expandable(&input, env_list);
		else if (*input == '$' && *(input + 1) == '?')
		{
			value = ft_itoa(EXIT_CODE);
			input = input + 2;
		}
		else if (*input == '$')
			value = handle_dollar(&input);
		else
			value = get_value(&input, 0);
		result = ft_strjoin(result, value, 1);
		ft_free(&value);
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
