/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SplitToken.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:00:05 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 18:00:07 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_detect(char *input, t_token **tokens, int i)
{
	char	tmp[2];
	int		j;

	j = -1;
	tmp[0] = '<';
	tmp[1] = '>';
	while (++j < 2)
	{
		if (input[i] == tmp[j] && input[i + 1] != tmp[j])
		{
			ft_lstadd_back(tokens, 1, REDIR, i);
			return (1);
		}
		else if (input[i] == tmp[j] && input[i + 1] == tmp[j])
		{
			ft_lstadd_back(tokens, 2, REDIR, i);
			return (2);
		}
	}
	if (input[i] == '|')
	{
		ft_lstadd_back(tokens, 1, PIPE, i);
		return (1);
	}
	return (0);
}

void	handle_qts(int *i, char *input, int *env_flag)
{
	int	flag_quote;
	int	k;

	flag_quote = 0;
	k = *i;
	(*i)++;
	while (input[*i] && input[*i] != input[k])
	{
		if (input[*i] == '$' && flag_quote == 0 && input[k] == '\"')
			*env_flag = 1;
		(*i)++;
	}
	if (input[*i] == input[k])
		flag_quote = 1;
	(*i)++;
}

int	handle_env_cmd(int j, int *i, t_token **tokens, int env_flag)
{
	if (j == *i)
		return (0);
	if (env_flag)
		ft_lstadd_back(tokens, *i - j, ENV, j);
	else
		ft_lstadd_back(tokens, *i - j, CMD, j);
	return (1);
}

int	is_word(t_token **tokens, char *input, int *i)
{
	int	j;
	int	env_flag;

	j = *i;
	env_flag = 0;
	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			handle_qts(i, input, &env_flag);
			continue ;
		}
		if (input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
		{
			if (input[*i] == '\'' || input[*i] == '\"')
				continue ;
			if (input[*i] && ft_isspace(input[*i]))
				break ;
			if (input[(*i)++] == '$')
				env_flag = 1;
		}
		else
			break ;
	}
	return (handle_env_cmd(j, i, tokens, env_flag));
}

void	split_tokens(char *input, t_token **tokens)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (is_word(tokens, input, &i))
			continue ;
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			i += redirection_detect(input, tokens, i);
			continue ;
		}
		i++;
	}
}
