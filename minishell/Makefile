NAME  = minishell

SRC_FOLDER = ./src/
HEADER_FOLDER = ./includes/
LIBFT_FOLDER = ./libft/

READLINE_FOLDER = $(shell brew --prefix readline)/lib/
HEADER_READLINE_FOLDER = $(shell brew --prefix readline)/include/

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS_F = minishell.c cd.c count_ut.c\
		echo.c env_ut.c env_utils.c env.c exec_ut.c\
		error.c exec_ut2.c exec.c exit.c export.c free.c lexer.c n_libft.c\
		new_split.c parse_ut.c parse.c pipe.c pwd.c lexer2.c  redir_out.c\
		redir_out2.c redir_ut.c redir.c redirection.c signal.c split_quotes.c\
		unset.c utils.c	utils2.c utils3.c utils4.c

HEADERS_F = minishell.h ft_structs.h

SRCS = $(addprefix $(SRC_FOLDER), $(SRCS_F))
HEADERS = $(addprefix $(HEADER_FOLDER), $(HEADERS_F))

LIBFT= $(LIBFT_FOLDER)libft.a

OTHER_DEPEND = \
Makefile

OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 
RM		=	rm -f 

ALL_LIBS	= \
-L $(READLINE_FOLDER) -lreadline \
-L $(LIBFT_FOLDER) -lft
ALL_HEADERS = \
-I $(HEADER_READLINE_FOLDER) \
-I $(LIBFT_FOLDER) \
-I $(HEADER_FOLDER)

all:	$(NAME)

$(LIBFT): libft ;

%.o:	%.c
	$(CC) -c $(CFLAGS) $(ALL_HEADERS) $< -o $@

$(NAME):	$(LIBFT) $(OTHER_DEPEND) $(OBJS) $(HEADERS) 
	$(CC) $(CFLAGS) $(OBJS) $(ALL_LIBS) $(ALL_HEADERS) -o $(NAME)

libft:
	@make -C $(LIBFT_FOLDER)

clean:
	@$(RM) $(OBJS)
	@make -C libft clean

fclean:	clean
	@$(RM) $(NAME)
	@make -C libft fclean

re:	fclean $(NAME)

.PHONY:	all libft clean fclean re