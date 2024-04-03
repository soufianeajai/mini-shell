#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

int					EXIT_CODE;

typedef enum s_node_type
{
	CMD,
	PIPE,
	REDIR,
	ENV,
}					t_node_type;

typedef struct s_token
{
	int				len;
	int				index;
	t_node_type		type;
	char			*str_qoutes;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
	int				flag_env;
	int				type_qoutes;
}					t_token;
struct termios		orig_termios;

// check first herdoc  '<<' !!
typedef struct s_cmd
{
	char			*cmd;
	char *cmd_path; // after get cmd , i need to get the path of the cmd
	char			**args;
}					t_cmd;

// syntax error :
int					check_syntax(t_token *tok);
void				printf_error_syntax(char *str);
int					is_operator(t_node_type type, int len, char *str);

// libft
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *s);
char				*ft_strjoin(char *s1, char *s2, int free_flag);
char				*ft_strdup(char *src);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memset(void *s, int c, size_t len);
void				ft_bzero(void *s, size_t n);
int					ft_strchr(const char *s, int c);
void				ft_putstr_fd(char *s, int fd);
size_t				count_strings(char **strings);
int					ft_isspace(char c);
void				ft_free(char **str);
void				*free_str_list(char **str);
char				*ft_itoa(int n);
char				*ft_substr(char *s, unsigned int start, size_t len);
size_t				my_atoi(const char *str);
int					ft_isdigit(int c);

// tokenisation
extern void			rl_replace_line(const char *, int);
void				free_tokens(t_token **tokens);
void				tokenisation(t_token **tokens, char *input);
void				split_tokens(char *input, t_token **tokens);
void				print_tokens(t_token *tokens);
char				*mystrdup(t_token *tokens, char *input);
void				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				handling_qoutes(t_token **t);
int					is_qoutes(char c, t_token **tok);
int 				detect_qts_exist(char *str);

#endif
