#include "../minishell.h"

int ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return;
	write(fd, s, ft_strlen(s));
}

size_t count_strings(char **strings)
{
	size_t count;

	count = 0;
	while (strings[count] != NULL)
		count++;
	return count;
}

int ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
