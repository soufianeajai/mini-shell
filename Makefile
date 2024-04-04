NAME = minishell
SRCS = libft/utils1.c libft/utils2.c libft/utils3.c libft/ft_split.c libft/utils4.c \
tokenisation/SplitToken.c syntax/syntax.c tokenisation/tokenisation.c tokenisation/util3_token.c tokenisation/util2_token.c tokenisation/utils_token.c \
environnement/env.c environnement/utils.c environnement/utils_env.c\
builtins/builtins_functions.c builtins/ft_echo.c builtins/ft_pwd.c \
builtins/ft_cd.c builtins/ft_env.c builtins/ft_unset.c builtins/ft_export.c builtins/ft_exit.c \
parsing/parsing.c parsing/util_expaind1.c parsing/parse_redirection_util.c parsing/util_expaind2.c parsing/free_tree.c parsing/utils.c parsing/parse_redirection.c parsing/expand_env.c parsing/get_arguments.c parsing/parsing_utils.c  execution/execute_tree.c \
execution/execute_simple_cmd.c execution/util_smp_cmd1.c execution/util_smp_cmd2.c execution/util_tree1.c execution/util_tree2.c main.c  handle_signals.c minishell_utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
all : $(NAME)
#-g3 -fsanitize=address
$(NAME) : $(OBJS)
	cc  -g3 $(CFLAGS)   -o $@ $^ -lreadline  -L /Users/$(USER)/Desktop/homebrew/opt/readline/lib -I /Users/$(USER)/Desktop/homebrew/opt/readline/include

clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

re : fclean all