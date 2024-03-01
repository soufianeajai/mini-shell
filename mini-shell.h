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

#define WORD 0
#define PIPE 1
#define I_RED 2
#define O_RED 3
#define APP 4
#define HER_DOC 5

typedef struct s_token
{
	int len;
	int index;
	int type;
	char *str;
	struct s_token *next;
} t_token;


typedef struct s_tree
{
    char *value; 
    struct s_tree *left;
    struct s_tree *right;
	int type;

} t_tree;

// check first herdoc  '<<' !!
typedef struct s_cmd 
{
	char *cmd;
	char *cmd_path; // after get cmd , i need to get the path of the cmd	
	char **args;
}			t_cmd;

// typedef struct s_command
// {
// 	t_cmd *cmd;               // The command to execute
// 	char *input_redirection;  // '<' The file to redirect input from,or NULL  no input redirection
// 	char *output_redirection; // '>' The file to redirect output to,or NULL  no output redirection
// 	int append;               // '>>' 1 if output redirection should append,0 otherwise
// 	int quote_type;           // 0 for no quotes, 1 for single quotes,2 for double quotes
// 	struct s_command *next;   // The next command in the list
// }			t_command;

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

// error
int 		syntax_token(char *input);
int			is_token(char c, char next, int *flag, char *token);
void		error(void);
void		error_fd(int fd, char *file, int free_allocation);
void		error_cmd(char *cmd);
void		ft_free(char **tab); 

// parsing
char		**split_commands(char *input);

void		ft_exit(char *input);
void		ft_pwd(char *input);
void		ft_clear(char *input);



//tokenisation
void tokenisation(t_token **tokens, char *input);
void print_tokens(t_token *tokens);