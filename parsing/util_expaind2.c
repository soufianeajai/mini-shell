/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_expaind2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:50:50 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:50:52 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
