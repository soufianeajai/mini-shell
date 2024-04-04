/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_expaind1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:50:43 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:50:45 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../environnement/env.h"

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
