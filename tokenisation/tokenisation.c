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
void	handling_qoutes_util(int *i, int *flag, t_token *tmp)
{
	if (tmp->str[*i] && *flag == is_qoutes(tmp->str[*i], &tmp))
	{
		*i = *i + 1;
		*flag = 0;
	}
}

int detect_qts_exist(char *str)
{
	int i;
	int qts;

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
char *hand_qts_tab(char *str)
{
	int i;
	int j;
	char *stock;


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


void	handling_qoutes(t_token **tk)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		flag;
	char	stock[100];
	tmp = *tk;
	flag = 0;

	
	while (tmp)
	{
		j = 0;
		i = 0;
		//printf("Handling qoutes %s\n", tmp->str);
		
		
		while (tmp->str && tmp->str[i])
		{
            flag = is_qoutes(tmp->str[i], &tmp);
			if (flag)
				i++;
			while (tmp->str[i] && (!is_qoutes(tmp->str[i], &tmp)
					|| (flag != is_qoutes(tmp->str[i], &tmp) && flag != 0)))
				stock[j++] = tmp->str[i++];
			handling_qoutes_util(&i, &flag, tmp);
		}
		stock[j] = '\0';
		if (detect_qts_exist(tmp->str) != 0)
			tmp->str_qoutes = hand_qts_tab(tmp->str);
		//printf("\nstock qoutes %s\n", tmp->str_qoutes);
		ft_free(&(tmp->str));
		tmp->str = ft_strdup(stock);
		tmp = tmp->next;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->str);
		tmp->str = 0;
		free(tmp->str_qoutes);
		tmp->str_qoutes = 0;
		free(tmp);
		tmp = 0;
	}
	tokens = 0;
}
