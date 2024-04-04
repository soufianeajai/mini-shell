/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:13 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:36:15 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		nbr_elements;
	long	nbr;

	nbr = n;
	nbr_elements = my_len(n);
	str = (char *)malloc(nbr_elements + 1);
	if (!str)
		return (0);
	str[nbr_elements] = 0;
	if (nbr == 0)
		str[0] = '0';
	else if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	while (nbr > 0)
	{
		str[--nbr_elements] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	return (str);
}

void	ft_free(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	my_atoi(const char *str)
{
	size_t	res;
	int		sign;
	size_t	tmp;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		tmp = res * 10 + (*str - '0');
		if (sign == 1 && tmp > LONG_MAX)
			return (SIZE_MAX);
		if (sign == -1 && (long long)(-tmp) < LONG_MIN)
			return (SIZE_MAX);
		res = tmp;
		str++;
	}
	return (sign * res);
}
