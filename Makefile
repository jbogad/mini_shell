# NAME		= minishell

# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer
# CFLAGS		= -Wall -Wextra -Werror
# CFLAGS		= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

# LIBFT_DIR	= src/libft
# LIBFT_LIB	= src/libft/libft.a

# SRC_UTILS = src/utils/utils.c
# SRC_BUILTINS = src/builtins/pwd.c src/builtins/echo.c src/builtins/export.c \
# 				src/builtins/utils_export.c src/builtins/exit.c src/builtins/env.c \
# 				src/builtins/unset.c src/builtins/cd.c
# SRC_UTILS_GLOBAL = src/utils_global/utils_to_env.c src/utils_global/utils_to_free.c
# SRC_EXEC = src/exec/exec.c src/exec/pipes.c src/exec/pipes_utils.c src/exec/pipes_cmd.c src/exec/pipes_child.c src/exec/redirections.c src/exec/redirections_utils.c src/exec/redirections_input.c src/exec/redirections_output.c
# SRC_PARSER = src/parser/read_input.c src/parser/get_short_path.c src/parser/extract_word_tokens.c \
#              src/parser/extract_ops_tokens.c src/parser/extract_quotes_dob_tokens.c \
#              src/parser/extract_quotes_sim_tokens.c src/parser/extract_all_tokens.c \
#              src/parser/extract_ops_tokens_utils.c src/parser/expansor.c src/parser/expand_tokens.c \
#              src/parser/heredoc.c
# SRC_SIGNALS = src/signals/signals.c
# LIBS = -lreadline
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
# 	@$(CC) $(CFLAGS) -c $< -o $@

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
SRC_UTILS_GLOBAL = src/utils_global/utils_to_env.c src/utils_global/utils_to_free.c src/utils_global/utils_export_add.c
SRC_EXEC = src/exec/exec.c src/exec/external_exec.c src/exec/pipes.c src/exec/pipes_utils.c src/exec/pipes_cmd.c src/exec/pipes_child.c src/exec/utils_pipes.c src/exec/redirections.c src/exec/redirections_utils.c src/exec/redirections_input.c src/exec/redirections_output.c
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

# 🎨 COLORES Y EFECTOS VISUALES
RESET		= \033[0m
BOLD		= \033[1m
DIM			= \033[2m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
BLINK		= \033[5m

# Colores básicos
BLACK		= \033[0;30m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m

# Colores brillantes
BRIGHT_BLACK	= \033[0;90m
BRIGHT_RED		= \033[0;91m
BRIGHT_GREEN	= \033[0;92m
BRIGHT_YELLOW	= \033[0;93m
BRIGHT_BLUE		= \033[0;94m
BRIGHT_MAGENTA	= \033[0;95m
BRIGHT_CYAN		= \033[0;96m
BRIGHT_WHITE	= \033[0;97m

# Colores con negrita
B_BLACK		= \033[1;30m
B_RED		= \033[1;31m
B_GREEN		= \033[1;32m
B_YELLOW	= \033[1;33m
B_BLUE		= \033[1;34m
B_MAGENTA	= \033[1;35m
B_CYAN		= \033[1;36m
B_WHITE		= \033[1;37m

# Fondos
BG_BLACK	= \033[40m
BG_RED		= \033[41m
BG_GREEN	= \033[42m
BG_YELLOW	= \033[43m
BG_BLUE		= \033[44m
BG_MAGENTA	= \033[45m
BG_CYAN		= \033[46m
BG_WHITE	= \033[47m

# 🚀 HEADER ÉPICO CON DEGRADADO
HEADER = "\n$(B_CYAN)\
╔═══════════════════════════════════════════════════════════════════════╗\n\
║  $(B_MAGENTA)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗$(B_CYAN)  ║\n\
║  $(B_MAGENTA)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║$(B_CYAN)  ║\n\
║  $(B_BLUE)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║$(B_CYAN)  ║\n\
║  $(B_BLUE)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║$(B_CYAN)  ║\n\
║  $(B_GREEN)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(B_CYAN) ║\n\
║  $(B_GREEN)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(B_CYAN) ║\n\
╚═══════════════════════════════════════════════════════════════════════╝$(RESET)\n\
\n\
$(B_YELLOW)                    � MODO COMPILACIÓN ACTIVADO 🔥$(RESET)\n\
$(B_GREEN)                      ═══════════════════════════$(RESET)\n\
$(B_MAGENTA)$(BLINK)                      ⚡ MASTODONTES POWER ⚡$(RESET)\n\
$(B_CYAN)                     💎 jaboga-d & clalopez �$(RESET)\n\
$(B_GREEN)                      ═══════════════════════════$(RESET)\n"

# 📊 MENSAJES CON PROGRESS BAR
COMPILE_MSG = "$(B_GREEN)[$(B_YELLOW)⚡$(B_GREEN)]$(RESET) $(B_CYAN)Compilando$(RESET): $(B_MAGENTA)"
LIBFT_MSG = "$(B_BLUE)[$(B_YELLOW)📚$(B_BLUE)]$(RESET) $(B_CYAN)Construyendo libft$(RESET)..."
LINK_MSG = "$(B_YELLOW)[$(B_RED)🔗$(B_YELLOW)]$(RESET) $(B_GREEN)Enlazando ejecutable$(RESET): $(B_MAGENTA)"
CLEAN_MSG = "$(B_RED)[$(B_YELLOW)🧹$(B_RED)]$(RESET) $(B_YELLOW)Limpiando archivos objeto$(RESET)..."
FCLEAN_MSG = "$(B_RED)[$(B_YELLOW)🗑️$(B_RED)]$(RESET) $(B_RED)Eliminando todo$(RESET)..."

# 🎉 MENSAJE DE ÉXITO ÉPICO
SUCCESS_MSG = "\n$(B_GREEN)\
╔════════════════════════════════════════════════════════════╗\n\
║                    $(B_YELLOW)✨ COMPILACIÓN EXITOSA ✨$(B_GREEN)                   ║\n\
║                                                            ║\n\
║               $(B_CYAN)� Minishell listo para la acción �$(B_GREEN)              ║\n\
║                                                            ║\n\
║                   $(B_MAGENTA)🚀 Ejecuta: $(B_WHITE)./minishell$(B_GREEN)                    ║\n\
║                                                            ║\n\
║           $(B_YELLOW)💪 Hecho por los MASTODONTES jaboga & clalopez 💪$(B_GREEN)      ║\n\
╚════════════════════════════════════════════════════════════╝$(RESET)\n"

# 🎯 TARGETS PRINCIPALES
all: header $(NAME)

header:
	@echo $(HEADER)
	@sleep 0.5

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo $(LINK_MSG)$(NAME)$(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo $(SUCCESS_MSG)
	@echo "$(B_GREEN)🎊 ¡Build completado en $$(date +%T)! 🎊$(RESET)"

$(LIBFT_LIB):
	@echo $(LIBFT_MSG)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "$(B_GREEN)[✅] Libft construida exitosamente$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo $(COMPILE_MSG)$(notdir $<)$(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(DIM)$(GREEN)   └─ $(notdir $@) generado$(RESET)"

clean:
	@echo $(CLEAN_MSG)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(B_GREEN)[✅] Limpieza completada$(RESET)"

fclean: clean
	@echo $(FCLEAN_MSG)
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(B_GREEN)[✅] Limpieza total completada$(RESET)"

# 🔄 REBUILD CON ESTILO
re: 
	@echo "$(B_YELLOW)🔄 Iniciando rebuild completo...$(RESET)"
	@$(MAKE) -s fclean
	@echo "$(B_CYAN)🔧 Reconstruyendo desde cero...$(RESET)"
	@$(MAKE) -s all

# 🧪 TARGET PARA TESTING
test: $(NAME)
	@echo "$(B_CYAN)🧪 Ejecutando tests...$(RESET)"
	@./test_minishell.sh || true

# 📋 TARGET PARA NORMINETTE
norm:
	@echo "$(B_MAGENTA)📋 Verificando norminette...$(RESET)"
	@norminette $(SRC) | grep -v "OK!" || echo "$(B_GREEN)[✅] ¡Todo OK con norminette!$(RESET)"

# 🎯 HELP CON ESTILO
help:
	@echo "$(B_CYAN)╔══════════════════════════════════════╗$(RESET)"
	@echo "$(B_CYAN)║$(B_YELLOW)          COMANDOS DISPONIBLES          $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)╠══════════════════════════════════════╣$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make$(RESET)       - Compilar el proyecto    $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make clean$(RESET) - Limpiar objetos         $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make fclean$(RESET)- Limpieza total          $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make re$(RESET)    - Recompilar todo         $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make test$(RESET)  - Ejecutar tests          $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)║$(RESET) $(B_GREEN)make norm$(RESET)  - Verificar norminette     $(B_CYAN)║$(RESET)"
	@echo "$(B_CYAN)╚══════════════════════════════════════╝$(RESET)"

.PHONY: all clean fclean re header test norm help