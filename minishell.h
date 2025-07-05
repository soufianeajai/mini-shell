/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajaite <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:57:05 by sajaite           #+#    #+#             */
/*   Updated: 2024/04/04 21:57:11 by sajaite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern int						g_exitcode;

typedef enum s_node_type
{
	CMD,
	PIPE,
	REDIR,
	ENV,
}						t_node_type;

typedef struct s_token
{
	int					len;
	int					index;
	t_node_type			type;
	char				*str_qoutes;
	char				*str;
	struct s_token		*prev;
	struct s_token		*next;
	int					flag_env;
	int					type_qoutes;
}						t_token;

// check first herdoc  '<<' !!
typedef struct s_cmd
{
	char				*cmd;
	char				*cmd_path;
	char				**args;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					flag;
	struct s_env		*next;
}						t_env;

typedef enum s_redir_type
{
	IN,
	OUT,
	APPEND,
	HER_DOC,
}						t_redir_type;

typedef struct s_tree_node
{
	t_node_type			type;
	void				*node;
}						t_tree_node;

typedef struct s_pipe_node
{
	t_node_type			type;
	t_tree_node			*right;
	t_tree_node			*left;
}						t_pipe_node;

typedef struct s_cmd_node
{
	t_node_type			type;
	char				*executable;
	char				**arguments;
	int					flag_env;
	int					type_qoutes;
}						t_cmd_node;

typedef struct s_redir_node
{
	t_node_type			type;
	t_redir_type		redir_type;
	t_cmd_node			*cmd;
	char				*filename;
	struct s_redir_node	*next;
}						t_redir_node;

// syntax error :
int						check_syntax(t_token *tok);
void					printf_error_syntax(char *str);
int						is_operator(t_node_type type, int len, char *str);

// libft
int						ft_strcmp(const char *s1, const char *s2);
char					**ft_split(char const *s, char c);
size_t					ft_strlen(const char *s);
char					*ft_strjoin(char *s1, char *s2, int free_flag);
char					*ft_strdup(char *src);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					*ft_memset(void *s, int c, size_t len);
void					ft_bzero(void *s, size_t n);
int						ft_strchr(const char *s, int c);
void					ft_putstr_fd(char *s, int fd);
size_t					count_strings(char **strings);
int						ft_isspace(char c);
void					ft_free(char **str);
void					*free_str_list(char **str);
char					*ft_itoa(int n);
char					*ft_substr(char *s, unsigned int start, size_t len);
size_t					my_atoi(const char *str);
int						ft_isdigit(int c);
int						my_len(int nbr);

// tokenisation
extern void				rl_replace_line(const char *str, int i);
void					free_tokens(t_token **tokens);
void					no_expaind_her_doc(t_token **token);
void					tokenisation(t_token **tokens, char *input);
void					split_tokens(char *input, t_token **tokens);
void					print_tokens(t_token *tokens);
char					*mystrdup(t_token *tokens, char *input);
void					ft_strlcpy(char *dst, const char *src, size_t dstsize);
void					handling_qoutes(t_token **t);
int						is_qoutes(char c, t_token **tok);
int						detect_qts_exist(char *str);
void					handling_qoutes_util(int *i, int *flag, t_token *tmp);
t_token					*create_node(int len, t_node_type type, int index);
void					ft_lstadd_back(t_token **lst, int len, t_node_type type,
							int index);
void					handling_qoutes2(t_token **tk);
void					handle_signals(void);
char					*get_node(t_tree_node *tree);
char					*hand_qts_tab(char *str);

#endif
