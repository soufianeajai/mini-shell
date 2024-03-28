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