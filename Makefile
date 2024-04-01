NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/utils3.c libft/ft_split.c \
tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c \
environnement/env.c environnement/utils.c\
builtins/builtins_functions.c builtins/ft_echo.c builtins/ft_pwd.c \
builtins/ft_cd.c builtins/ft_env.c builtins/ft_unset.c builtins/ft_export.c builtins/ft_exit.c \
parsing/parsing.c parsing/free_tree.c parsing/utils.c parsing/parse_redirection.c parsing/expand_env.c parsing/get_arguments.c parsing/parsing_utils.c  execution/execute_tree.c \
execution/execute_simple_cmd.c mini-shell.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)
#%.o: %.c #builtins/ft_export.c builtins/ft_unset.c builtins/ft_env.c -fsanitize=address\
#    cc $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	cc  -g3 $(CFLAGS)   -o $@ $^   -lreadline -L /Users/$(USER)/Desktop/homebrew/opt/readline/lib -I /Users/$(USER)/Desktop/homebrew/opt/readline/include

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all

