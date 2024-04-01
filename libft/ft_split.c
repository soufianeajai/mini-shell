/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:41:25 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/01 19:11:58 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*word(char const *s, char c)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	len = ft_len(s, c);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (*s && *s != c)
	{
		p[i] = *s;
		i++;
		s++;
	}
	p[len] = '\0';
	return (p);
}

static int	count_w(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 1;
	while (s[i])
	{
		while (s[i] == c)
		{
			in_word = 1;
			i++;
		}
		while (s[i] && s[i] != c)
		{
			if (in_word)
			{
				count++;
				in_word = 0;
			}
			i++;
		}
	}
	return (count);
}

static char	**free_all(char **t, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(t[i]);
		i++;
	}
	free(t);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**p;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(p = (char **)malloc(sizeof(char *) * (count_w(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		p[j] = word(s + i, c);
		if (!p[j])
			return (free_all(p, j));
		j++;
		while (s[i] && s[i] != c)
			i++;
	}
	p[j] = NULL;
	return (p);
}
