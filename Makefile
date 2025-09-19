NAME = minishell
CC = cc

# Detección automática del sistema operativo
UNAME_S := $(shell uname -s)

# Configuración para macOS
ifeq ($(UNAME_S),Darwin)
	CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/Cellar/readline/8.3.1/include
	LIBS = -lreadline -L/opt/homebrew/Cellar/readline/8.3.1/lib
endif

# Configuración para Linux (Ubuntu)
ifeq ($(UNAME_S),Linux)
	CFLAGS = -Wall -Wextra -Werror -I/usr/include/readline
	LIBS = -lreadline
endif

LIBFT_DIR = src/libft
LIBFT_LIB = src/libft/libft.a

# Mensajes bonitos
HEADER = "\n\033[1;36m\
┌─────────────────────────────────────────────────────────────────────┐\n\
│  ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      │\n\
│  ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      │\n\
│  ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      │\n\
│  ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      │\n\
│  ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ │\n\
│  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ │\n\
└─────────────────────────────────────────────────────────────────────┘\n\
\033[0m\033[1;32m                    🚀 COMPILANDO PROYECTO... 🚀\033[0m\n\
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

# Archivos fuente
SRC = src/minishell.c \
      src/parser/read_input.c src/parser/get_short_path.c src/parser/extract_word_tokens.c \
      src/parser/heredoc.c src/parser/extract_all_tokens.c src/parser/expand_tokens.c \
      src/parser/extract_ops_tokens.c src/parser/extract_quotes_dob_tokens.c \
      src/parser/extract_quotes_sim_tokens.c src/parser/extract_ops_tokens_utils.c \
      src/parser/expansor.c \
      src/signals/signals.c \
      src/builtins/pwd.c src/builtins/echo.c src/builtins/export.c \
      src/builtins/unset.c src/builtins/cd.c src/builtins/env.c \
      src/builtins/exit.c src/builtins/utils_export.c \
      src/exec/exec.c src/exec/exec_help.c src/exec/external_exec.c src/exec/external_exec_help.c src/exec/pipes.c src/exec/pipes_utils.c src/exec/pipes_cmd.c \
      src/exec/pipes_child.c src/exec/utils_pipes.c src/exec/redirections.c src/exec/redirections_utils.c \
      src/exec/redirections_input.c src/exec/redirections_output.c \
      src/utils/utils.c \
      src/utils_global/utils_to_env.c src/utils_global/utils_to_free.c src/utils_global/utils_export_add.c src/utils_global/heredoc_utils.c src/utils_global/tokens_utils.c

OBJ_DIR = objects
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: header $(NAME)

header:
	@echo $(HEADER)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo $(LINK_MSG)$(NAME)'\033[0m'
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo $(SUCCESS_MSG)

$(LIBFT_LIB):
	@echo "\033[1;94m[📚]\033[0m Compilando libft..."
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo $(COMPILE_MSG)$<'\033[0m'
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;31m[🧹]\033[0m Limpiando archivos objeto..."
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "\033[1;31m[🗑️]\033[0m Eliminando ejecutable..."
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re header
