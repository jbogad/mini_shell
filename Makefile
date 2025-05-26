NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= src/libft
LIBFT_LIB	= src/libft/libft.a

SRC		= src/minishell.c
OBJS		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
