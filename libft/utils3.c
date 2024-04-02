#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (len--)
		*p++ = (unsigned char)c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static int	my_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

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
