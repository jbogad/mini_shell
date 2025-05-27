NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= src/libft
LIBFT_LIB	= src/libft/libft.a

#Aqui ves poniendo las rutas de los archivos y luego lo metes en src y si necesitas alguna lib metela en libs BRRRRRRRRRR
#SRC_BUILTINS =
#SRC_EXEC = 
SRC_PARSER = src/parser/read_input.c
SRC_SIGNALS = src/signals/signals.c
LIBS = -lreadline

SRC		= src/minishell.c $(SRC_PARSER) $(SRC_SIGNALS)
OBJS		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

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
