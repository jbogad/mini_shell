NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= src/libft
LIBFT_LIB	= src/libft/libft.a

SRC_UTILS = src/utils/utils.c
SRC_BUILTINS = src/builtins/pwd.c src/builtins/echo.c src/builtins/cd.c
SRC_EXEC = src/exec/exec.c 
SRC_PARSER = src/parser/read_input.c src/parser/get_short_path.c src/parser/extract_tokens.c \
			 src/parser/extract_ops_tokens.c src/parser/extract_quotes_dob_tokens.c \
			 src/parser/extract_quotes_sim_tokens.c
SRC_SIGNALS = src/signals/signals.c
LIBS = -lreadline

SRC		= src/minishell.c $(SRC_PARSER) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXEC) $(SRC_UTILS)
OBJS	= $(SRC:.c=.o)


all: header $(NAME)

header:
	@echo $(HEADER)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

HEADER = "\n\033[1;36m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\n\033[0m\
                MASTODONTES DEEEEEEEEEE:                    		\n\
\t\t--- \033[1;36mclalopez\033[0m && \033[1;36mjaboga-d\033[0m --- \n"


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re header
