/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:01:19 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 18:01:21 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return ;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*mystrdup(t_token *tokens, char *input)
{
	char	*token;

	token = malloc(sizeof(char) * (tokens->len + 1));
	if (token == NULL)
		return (NULL);
	ft_strlcpy(token, input + tokens->index, tokens->len + 1);
	return (token);
}

void	no_expaind_her_doc(t_token **token)
{
	t_token	*tok;

	tok = *token;
	while (tok)
	{
		if (tok->type == REDIR && !ft_strncmp(tok->str, "<<", 2))
		{
			if (tok->next != NULL && tok->next->type == ENV)
			{
				tok->next->type = CMD;
			}
		}
		tok = tok->next;
	}
}

void	tokenisation(t_token **tokens, char *input)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp->str = mystrdup(tmp, input);
		tmp = tmp->next;
	}
	tmp = NULL;
	no_expaind_her_doc(tokens);
}

int	is_qoutes(char c, t_token **tok)
{
	if (c == '\"')
	{
		if ((*tok)->type_qoutes == -1)
		{
			(*tok)->type_qoutes = 2;
		}
		return (2);
	}
	if (c == '\'')
	{
		if ((*tok)->type_qoutes == -1)
			(*tok)->type_qoutes = 1;
		return (1);
	}
	return (0);
}
