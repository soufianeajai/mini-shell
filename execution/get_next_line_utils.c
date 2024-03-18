/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:37:48 by afanidi           #+#    #+#             */
/*   Updated: 2023/11/17 16:50:57 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_ft_strdup(char *src)
{
	char	*p;
	int		lensrc;

	if (!src)
		return (0);
	lensrc = ft_ft_strlen(src);
	p = (char *)malloc(sizeof(char) * (lensrc + 1));
	if (!p)
		return (0);
	p = ft_ft_strcpy(p, src);
	return (p);
}

char	*ft_ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	char	*temp;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	temp = s1;
	str = malloc((ft_ft_strlen(s1) + ft_ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = 0;
	free(temp);
	temp = NULL;
	return (str);
}

int	check_new_line(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
