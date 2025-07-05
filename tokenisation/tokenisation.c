/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:00:31 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 18:00:32 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	util2(t_token **tmp)
{
	if (detect_qts_exist((*tmp)->str) != 0)
		(*tmp)->str_qoutes = hand_qts_tab((*tmp)->str);
	(*tmp) = (*tmp)->next;
}

void	handling_qoutes(t_token **tk)
{
	t_token	*tmp;
	tmp = *tk;
	while (tmp)
		util2(&tmp);
}

void	util_qts(t_token **tmp, char *stock)
{
	ft_free(&((*tmp)->str));
	(*tmp)->str = ft_strdup(stock);
	(*tmp) = (*tmp)->next;
}

void	handling_qoutes2(t_token **tk)
{
	t_token	*tmp;
	char	stock[1000];
	int		i;
	int		j;
	int		flag;

	tmp = *tk;
	flag = 0;
	while (tmp)
	{
		j = 0;
		i = 0;
		while (tmp->str && tmp->str[i])
		{
			flag = is_qoutes(tmp->str[i], &tmp);
			if (flag)
				i++;
			while (tmp->str[i] && (!is_qoutes(tmp->str[i], &tmp)
					|| (flag != is_qoutes(tmp->str[i], &tmp) && flag != 0)))
				stock[j++] = tmp->str[i++];
			handling_qoutes_util(&i, &flag, tmp);
		}
		stock[j] = '\0';
		util_qts(&tmp, stock);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->str);
		tmp->str = 0;
		free(tmp->str_qoutes);
		tmp->str_qoutes = 0;
		free(tmp);
		tmp = 0;
	}
	tokens = 0;
}
