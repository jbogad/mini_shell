NAME = libftprintf.a
CC = cc
CCFLAGS = -Wall -Wextra -Werror
SRC =	convert_char_string.c convert_numbers.c convert_pointer.c ft_printf.c
OBJ = $(SRC:.c=.o)
INCLUDE = ft_printf.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re