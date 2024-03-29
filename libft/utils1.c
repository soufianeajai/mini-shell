/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:40:45 by afanidi           #+#    #+#             */
/*   Updated: 2024/02/22 16:41:02 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && n - 1 != 0)
	{
		i++;
		n--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int free_flag)
{
	char	*str;
	size_t	i;
	char	*temp1;
	char	*temp2;

	i = 0;
	temp1 = s1;
	temp2 = s2;
	printf("yes\n");
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
//	if(!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
//		return (NULL);
	printf("no\n");
	while (temp1 && *temp1)
		str[i++] = *(temp1++);
	while (temp2 && *temp2)
		str[i++] = *(temp2++);
	str[i] = 0;
	if (free_flag == 1)
		ft_free(&s1);
	if (free_flag == 2)
		ft_free(&s2);
	if (free_flag == 3)
	{
		ft_free(&s1); 
		ft_free(&s2);
	}
	return (str);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	char	*temp;

// 	if (s1 == NULL)
// 	{
// 		s1 = malloc(sizeof(char));
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	temp = s1;
// 	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (*s1)
// 		str[i++] = *(s1++);
// 	while (*s2)
// 		str[i++] = *(s2++);
// 	str[i] = 0;
// 	free(temp);
// 	temp = NULL;
// 	return (str);
// }

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = ft_strlen(src);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src && src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

