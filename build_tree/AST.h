#include "../mini-shell.h"

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *input;
    char *output;
    int append;
} t_cmd;

typedef struct s_redir
{
    char *input;
    char *output;
    int append;
} t_redir;



typedef struct s_ast
{
    char *value;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

t_ast *create_node(char *value);
void free_tree(t_ast *tree);
void print_tree(t_ast *tree);
