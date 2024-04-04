/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:40:19 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 22:40:20 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detect_qts_exist(char *str)
{
	int	i;
	int	qts;

	i = 0;
	qts = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == '$')
			qts++;
		i++;
	}
	return (qts);
}

char	*hand_qts_tab(char *str)
{
	int		i;
	int		j;
	char	*stock;

	stock = malloc(sizeof(char) * (detect_qts_exist(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == '$')
			stock[j++] = str[i];
		i++;
	}
	stock[j] = '\0';
	return (stock);
}
