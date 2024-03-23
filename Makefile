NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/ft_split.c \
tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c \
environnement/env.c environnement/utils.c\
builtins/builtins_functions.c mini-shell.c \
parsing/parsing.c parsing/expand_env.c parsing/parsing_utils.c parsing/parse_redirection.c parsing/get_argumetns.c execution/execute_tree.c \
execution/execute_simple_cmd.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

#%.o: %.c
#    cc $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	cc  -g3 $(CFLAGS)  -fsanitize=address -o $@ $^ -lreadline

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all
