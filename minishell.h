#ifndef MINISHELL_H
#define MINISHELL_H
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

extern void	rl_replace_line(const char *, int);
//extern int	g_signal;


typedef enum
{
	CMD,
	PIPE,
	REDIR,
	ENV,
}						node_type;

typedef struct s_token
{
	int					len;
	int					index;
	node_type			type;
	char				*str;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;


// check first herdoc  '<<' !!
typedef struct s_cmd 
{
	char *cmd;
	char *cmd_path; // after get cmd , i need to get the path of the cmd	
	char **args;
}			t_cmd;

//syntax error : 
int check_syntax(t_token *tok);
void printf_error_syntax(char *str);
int    is_operator(node_type type,int len ,char *str);

// libft
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
size_t		count_strings(char **strings);
int			ft_isspace(char c);
void	ft_free(char **tab);


//tokenisation
void free_tokens(t_token **tokens);
void tokenisation(t_token **tokens, char *input);
void SplitTokens(char *input, t_token **tokens);
void print_tokens(t_token *tokens);
char *mystrdup(t_token *tokens, char *input);
void ft_strlcpy(char *dst, const char *src, size_t dstsize);
void handling_qoutes(t_token **t);
int is_qoutes(char c);


#endif
