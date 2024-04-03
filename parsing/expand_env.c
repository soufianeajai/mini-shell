#include "../environnement/env.h"
#include "parsing.h"
#include <fcntl.h>

void	expand_env(t_token **token, t_env *env_list)
{
	t_token	*temp;
	char	*value;
	char	**temp_str;

	temp = *token;
	while (temp)
	{
		if (temp->type == ENV)
		{
			temp_str = &temp->str;
			value = get_env_value(temp->str, env_list,temp->str_qoutes);
			ft_free(temp_str);
			if (value && *value == '\0')
				ft_free(&value);
			else
				temp->str = value;
			temp->type = CMD;
		}
		temp = temp->next;
	}
}

char	*handle_expandable(char **input, t_env *env_list)
{
	char	*key;
	char	*value;

	key = 0;
	value = 0;
	
	if (**input == '$' && isalpha_num(*((*input) + 1)))
	{
		if (is_alpha(*((*input) + 1)))
		{
			(*input)++;
			key = get_value(input, 1);
			value = ft_getenv(env_list, key);
			ft_free(&key);
		}
		else
		{
			*input = (*input + 2);
			value = get_value(input, 0);
		}
	}
	return (value);
}



int	checkfor_qoutes(char *tab_qoutes,int *i)
{
	printf("------>%s",tab_qoutes);
	while (tab_qoutes[*i])
	{
		if (tab_qoutes[*i] == '\'')
		{
			*i = *i + 1;
			while (tab_qoutes[*i] && tab_qoutes[*i] != '\'')
				*i = *i + 1;
			if (tab_qoutes[*i] && tab_qoutes[*i] == '\'')
				*i = *i + 1;
			printf("1 - i : %d\n",*i);
			return (0);
		}
		else if (tab_qoutes[*i] == '\"')
		{
			*i = *i + 1;
			while (tab_qoutes[*i] && tab_qoutes[*i] != '\"')
				*i = *i + 1;
			if (tab_qoutes[*i] && tab_qoutes[*i] == '\"')
			*i = *i + 1;
			printf("2 - i : %d\n",*i);
			return (1);
		}
		else
		{
			*i = *i + 1;
			printf("3 - i : %d\n",*i);
			return (1);
		}
		// else if (tab_qoutes[j] == '\"' && j == 0)
		// {
		// 	while(tab_qoutes[j] && tab_qoutes[++j] != '\"')
		// 		j++;
		// 	// tab[j] == "
		// 	*i += j + 1;
		// 	printf("i : %d\n",*i);
		// 	return (1);
		// }
		// else if (tab_qoutes[j] && tab_qoutes[j] == '\'' && j == 0)
		// {
		// 	while(tab_qoutes[j] == '\"')
		// 	{
		// 		(*i)++;
		// 		j++;
		// 	}
		// 	return (0);
		// }
		// j++;
	}
	return (1);
}
char	*get_env_value(char *input, t_env *env_list,char *tab_qoutes)
{
	char	*result;
	char	*value;
	int i = 0;

	result = NULL;
	value = NULL;
	while (input && *input)
	{
		//printf("\n\ninput : %s , qoutes : %s  -- %d\n\n",input,tab_qoutes,checkfor_qoutes(tab_qoutes,&i));
		if (*input == '$' && isalpha_num(*(input + 1)) && checkfor_qoutes(tab_qoutes,&i))
			
			value = handle_expandable(&input, env_list);
		
		
		
		else if (*input == '$' && *(input + 1) == '?')
		{
			value = ft_itoa(EXIT_CODE);
			input = input + 2;
		}
		else if (*input == '$')
		{
			input++;
			value = ft_strjoin("$", get_value(&input, 0), 2);
		}
		else
			value = get_value(&input, 0);
		result = ft_strjoin(result, value, 1);
		ft_free(&value);
	}
	return (result);
}

char	*get_value(char **str, int flag)
{
	char	*start;
	char	*value;
	char	temp;

	start = *str;
	value = 0;
	if (flag)
	{
		while (**str && isalpha_num(**str))
			(*str)++;
	}
	else
	{
		while (**str && **str != '$')
			(*str)++;
	}
	temp = **str;
	**str = '\0';
	value = ft_strdup(start);
	**str = temp;
	return (value);
}


// int *handle_expand_qoutes(char *input , char *oldstr, int start)
// {
// 	int i;
// 	int j;
// 	int flag;
	//OLD :  "$USER"'$PWD'
	//NEW :  $USER$PWD

	//NEW :  $USER$PWD
	//if $ index = 0 so return 0
	// if $ index = x check for index (x-1) if (' and  //check for oldster) so return 0 ,
	// "" so return 1



	//check for oldstr
	// first len = 3 , 
	// old  : search $ -> + len 

// }

// char	*handle_expandable(char **input, t_env *env_list, t_token *token)
// {
// 	char	*key;
// 	char	*value;

// 	key = 0;
// 	value = 0;
// 	if (**input == '$' && isalpha_num(*((*input) + 1)))
// 	{
// 		//,token->oldstr + (*input - token->str + 1)
// 		 printf("\n input :%s\n position:%s\n",*input,token->oldstr + (*input - token->str + 1));
// 		long index = *input - token->str;
// 		printf("index : %ld read jus $ : %d\n",index,read_$_len(*input + 1));

// 		if (is_alpha(*((*input) + 1)))
// 		{
// 			(*input)++;
// 			key = get_value(input, 1);
// 			value = ft_getenv(env_list, key);
// 			ft_free(&key);
// 		}
// 		else
// 		{
// 			*input = (*input + 2);
// 			value = get_value(input, 0);
// 		}
// 	}
// 	return (value);
// }