/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:49:26 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:49:27 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environnement/env.h"
#include "parsing.h"

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
