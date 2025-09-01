# NAME		= minishell

# CC			= cc
# # CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
# # CFLAGS		= -Wall -Wextra -Werror
# CFLAGS		= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

# LIBFT_DIR	= src/libft
# LIBFT_LIB	= src/libft/libft.a

# SRC_UTILS = src/utils/utils.c
# SRC_BUILTINS = src/builtins/pwd.c src/builtins/echo.c src/builtins/export.c \
# 				src/builtins/utils_export.c src/builtins/exit.c src/builtins/env.c \
# 				src/builtins/unset.c src/builtins/cd.c
# SRC_UTILS_GLOBAL = src/utils_global/utils_to_env.c src/utils_global/utils_to_free.c
# SRC_EXEC = src/exec/exec.c src/exec/pipes.c src/exec/utils_pipes.c
# SRC_PARSER = src/parser/read_input.c src/parser/get_short_path.c src/parser/extract_word_tokens.c \
#              src/parser/extract_ops_tokens.c src/parser/extract_quotes_dob_tokens.c \
#              src/parser/extract_quotes_sim_tokens.c src/parser/extract_all_tokens.c \
#              src/parser/extract_ops_tokens_utils.c src/parser/expansor.c src/parser/expand_tokens.c \
#              src/parser/heredoc.c
# SRC_SIGNALS = src/signals/signals.c
# # LIBS = -lreadline
# LIBS = -L/opt/homebrew/opt/readline/lib -lreadline

# SRC		= src/minishell.c $(SRC_PARSER) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXEC) $(SRC_UTILS) $(SRC_UTILS_GLOBAL)
# OBJ_DIR = objects
# OBJS	= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# HEADER = "\n\033[1;36m\
# ┌─────────────────────────────────────────────────────────────────────┐\n\
# │  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      │\n\
# │  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      │\n\
# │  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      │\n\
# │  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      │\n\
# │  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ │\n\
# │  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ │\n\
# └─────────────────────────────────────────────────────────────────────┘\n\
# \033[0m\
# \033[1;32m                    🚀 COMPILANDO PROYECTO... 🚀\033[0m\n\
# \033[1;33m                     ───────────────────────\033[0m\n\
# \033[1;35m                    👑 MASTODONTES DEEEEE 👑\033[0m\n\
# \033[1;94m                  🔥 clalopez && jaboga-d 🔥\033[0m\n\
# \033[1;32m                     ───────────────────────\033[0m\n"

# COMPILE_MSG = "\033[1;32m[✓]\033[0m Compilando: \033[1;36m"
# LINK_MSG = "\033[1;33m[🔗]\033[0m Enlazando ejecutable: \033[1;35m"
# SUCCESS_MSG = "\n\033[1;32m┌────────────────────────────────────────┐\n\
# │           ✨ COMPILACIÓN EXITOSA ✨     │\n\
# │                                        │\n\
# │    🎉 Proyecto listo para ejecutar 🎉  │\n\
# │                                        │\n\
# │         Ejecuta: \033[1;36m./minishell\033[1;32m          │\n\
# └────────────────────────────────────────┘\033[0m\n"

# CLEAN_MSG = "\033[1;31m[🧹]\033[0m Limpiando archivos objeto...\033[0m"
# FCLEAN_MSG = "\033[1;31m[🗑️ ]\033[0m Eliminando ejecutable y archivos objeto...\033[0m"

# all: header $(NAME)

# header:
# 	@echo $(HEADER)

# $(NAME): $(LIBFT_LIB) $(OBJS)
# 	@echo $(LINK_MSG)$(NAME)\033[0m
# 	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
# 	@echo $(SUCCESS_MSG)

# $(LIBFT_LIB):
# 	@echo "\033[1;34m[📚]\033[0m Compilando libft...\033[0m"
# 	@$(MAKE) -sC $(LIBFT_DIR)

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR);

# $(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
# 	@mkdir -p $(dir $@)
# 	@echo $(COMPILE_MSG)$<\033[0m
# 	@$(CC) $(CFLAGS) -I $(LIBS) -c -o $@ $<

# clean:
# 	@echo $(CLEAN_MSG)
# 	@rm -rf $(OBJ_DIR)
# 	@$(MAKE) -sC $(LIBFT_DIR) fclean

# fclean: clean
# 	@echo $(FCLEAN_MSG)
# 	@rm -f $(NAME)
# re: fclean all

# .PHONY: all clean fclean re header


NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

LIBFT_DIR	= src/libft
LIBFT_LIB	= src/libft/libft.a

SRC_UTILS = src/utils/utils.c
SRC_BUILTINS = src/builtins/pwd.c src/builtins/echo.c src/builtins/export.c \
                src/builtins/unset.c src/builtins/cd.c src/builtins/env.c \
                src/builtins/exit.c src/builtins/utils_export.c
SRC_UTILS_GLOBAL = src/utils_global/utils_to_env.c src/utils_global/utils_to_free.c
SRC_EXEC = src/exec/exec.c src/exec/pipes.c src/exec/pipes_utils.c src/exec/pipes_cmd.c src/exec/pipes_child.c src/exec/redirections.c src/exec/redirections_utils.c src/exec/redirections_input.c src/exec/redirections_output.c
SRC_PARSER = src/parser/read_input.c src/parser/get_short_path.c src/parser/extract_word_tokens.c \
             src/parser/heredoc.c src/parser/extract_all_tokens.c src/parser/expand_tokens.c \
             src/parser/extract_ops_tokens.c src/parser/extract_quotes_dob_tokens.c \
             src/parser/extract_quotes_sim_tokens.c src/parser/extract_ops_tokens_utils.c \
             src/parser/expansor.c
SRC_SIGNALS = src/signals/signals.c

LIBS = -L/opt/homebrew/opt/readline/lib -lreadline

SRC		= src/minishell.c $(SRC_PARSER) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXEC) $(SRC_UTILS) $(SRC_UTILS_GLOBAL)
OBJ_DIR = objects
OBJS	= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

HEADER = "\n\033[1;36m\
┌─────────────────────────────────────────────────────────────────────┐\n\
│  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      │\n\
│  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      │\n\
│  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      │\n\
│  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      │\n\
│  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ │\n\
│  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ │\n\
└─────────────────────────────────────────────────────────────────────┘\n\
\033[0m\
\033[1;32m                    🚀 COMPILANDO PROYECTO... 🚀\033[0m\n\
\033[1;33m                     ───────────────────────\033[0m\n\
\033[1;35m                    👑 MASTODONTES DEEEEE 👑\033[0m\n\
\033[1;94m                  🔥 clalopez && jaboga-d 🔥\033[0m\n\
\033[1;32m                     ───────────────────────\033[0m\n"

COMPILE_MSG = "\033[1;32m[✓]\033[0m Compilando: \033[1;36m"
LINK_MSG = "\033[1;33m[🔗]\033[0m Enlazando ejecutable: \033[1;35m"
SUCCESS_MSG = "\n\033[1;32m┌────────────────────────────────────────┐\n\
│           ✨ COMPILACIÓN EXITOSA ✨     │\n\
│                                        │\n\
│    🎉 Proyecto listo para ejecutar 🎉  │\n\
│                                        │\n\
│         Ejecuta: \033[1;36m./minishell\033[1;32m          │\n\
└────────────────────────────────────────┘\033[0m\n"

CLEAN_MSG = "\033[1;31m[🧹]\033[0m Limpiando archivos objeto...\033[0m"
FCLEAN_MSG = "\033[1;31m[🗑️ ]\033[0m Eliminando ejecutable y archivos objeto...\033[0m"

all: header $(NAME)

header:
	@echo $(HEADER)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo $(LINK_MSG)$(NAME)\033[0m
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo $(SUCCESS_MSG)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo $(COMPILE_MSG)$<\033[0m
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo $(CLEAN_MSG)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(FCLEAN_MSG)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re header