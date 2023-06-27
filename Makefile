SRCS = srcs/main.c srcs/env.c srcs/echo.c srcs/utils.c srcs/utils_exec.c srcs/exec.c srcs/parsing.c srcs/pipe.c srcs/ft_split_parse.c #srcs/here_doc.c

SRCS_BONUS	= 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Iincludes
NAME = minishell
NAME_BONUS =
RM = rm -f
LIBS = -Llibft -lft -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) -o $(NAME) $(OBJS) $(LIBS) 

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
		make -C libft -s
		$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBS)

debug: CFLAGS+=-g
debug: re

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)
		make clean -C libft

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)
		make fclean -C libft

re: fclean all

.PHONY: all fclean clean re debug bonus
