NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/ft_split.c \
tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c \
environnement/env.c environnement/utils.c\
builtins/builtins_functions.c builtins/ft_echo.c builtins/ft_pwd.c \
builtins/ft_cd.c builtins/ft_env.c builtins/ft_unset.c builtins/ft_export.c \
parsing/parsing.c parsing/parse_redirection.c parsing/expand_env.c parsing/get_argumetns.c parsing/parsing_utils.c  execution/execute_tree.c \
execution/execute_simple_cmd.c mini-shell.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)
#%.o: %.c #builtins/ft_export.c builtins/ft_unset.c builtins/ft_env.c \
#    cc $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	cc  -g3 $(CFLAGS)  -fsanitize=address -o $@ $^ -lreadline

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all
