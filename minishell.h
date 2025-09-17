/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:25 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/17 11:14:18 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "src/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# define GREEN_BRIGHT "\001\033[1;32m\002"
# define RESET "\001\033[0m\002"

// Variable global para manejar las señales del heredoc y minishell
extern volatile sig_atomic_t	g_skip_next_readline;

/* Estructura para guardar los tokens del input
cada token tendra su valor guardado
ej: TOKEN_WORD -> echo */
typedef enum e_token_type
{
	TOKEN_WORD,// comandos y argumntos
	TOKEN_PIPE,// |
	TOKEN_REDIR_IN,// <
	TOKEN_REDIR_OUT,// >
	TOKEN_APPEND,// >>
	TOKEN_HEREDOC,// <<
	TOKEN_SIM_QUOTE,// string entre comillas simples 'Hola'
	TOKEN_DOB_QUOTE,// string entre comillas doblres "Ho la"
}								t_token_type;

// Guarda cada elemento del comando parseado.
typedef struct s_token
{
	t_token_type	type;// tipo de token (pipe, word)
	char			*value;// contenido del token (echo, ls, etc)
	int				index;// indice del token (añadido de t_lexer)
	int				heredoc_fd;
	struct s_token	*next;// puntero al siguiente (añadido de t_lexer)
}								t_token;

// estructura para el parseo
typedef struct s_extract
{
	int	i;// indice actual
	int	start;// indice dentro del token
	int	count;// Contador de token
	int	index;// Indice del array de tokens
	int	in_sim_quote;// flag para dentro comillas simples
	int	in_dob_quote;// flag para dentro de comillas dobles
}								t_extract;

// Estructura para la expansión de variables
typedef struct s_expand
{
	int		i;// Indice para la expansión
	char	*result;// String tras expandir las variables
	char	*env;// Valor de la variable de entorno
	char	*var;// Nombre de la variable de entorno
	char	*tmp;// String temporal
	int		start;// Posicion del inicio de la variable
}								t_expand;

// Lista enlazada de las variables de entorno
typedef struct s_env
{
	char			*name_env;// Nombre de la variable ("HOME")
	char			*val_env;// Valor de la variable (ej:usr/bin)
	struct s_env	*next;// Puntero al siguiente
}								t_env;

// ELIMINADAS: t_lexer (duplicaba t_token)
typedef struct s_parser
{
	char			*cmd;// comando que será ejecutado
	int				redir_in;// redireccionamiento de entrada
	int				redir_out;// redireccionamiento de salida
	struct s_parser	*next;//  siguiente elemento en la lista
}								t_parser;

typedef struct s_shell
{
	char		**paths;// variables de entorno del sistema
	char		**cmd_args;// comando seguido de argumentos
	int			count_cmd_args;// cantidad de comando + argumentos
	t_env		*env;// lista de nodos que representa `envp`
	t_token		*tokens;// CAMBIADO: ahora usa t_token unificado
	t_parser	*parser;// lista de nodos que separa los comandos
	int			exit_status;// entero que representa el estado de salida
	int			shell_pid;// pid de la minishell cuando se inicia
}								t_shell;

typedef struct s_heredoc
{
	int		fd[2];//Pipe para leer o escribir
	pid_t	pid;//pid del proceso del heredoc
	char	*to_search;//Palabra a buscar
	t_env	*env_list;//Lista de las vars de entorno a expandir
	t_token	*token;//Tipo de token del heredoc
}	t_heredoc;

// Utils
char							*ft_strndup(const char *s, size_t n);
void							free_tokens(t_token **tokens);
int								ft_strcmp(const char *s1, const char *s2);
void							free_env(t_env *env_list);
int								get_shell_pid(void);

// Pipes helper structure
typedef struct s_pipe_data
{
	t_token						**tokens;
	int							cmd_idx;
	int							total;
	int							pipes[2][2];
	t_shell						*msh;
}								t_pipe_data;

/*================JAVIER================*/

/*pwd*/
void							ft_pwd(void);

/*echo*/
void							ft_echo(t_token **tokens, t_shell *msh);

/*exec*/
void							execute(t_token **tokens, t_shell *msh);
void							free_cmd_args(t_shell *msh);
char							*find_path(char *cmd, t_env *env);
void							execute_external_command(t_token **tokens,
									t_shell *msh);

/*export*/
void							ft_export(t_shell *msh);

/*utils_export*/
void							add_arg_to_env(char *var, t_shell *msh);
int								is_valid_name(char *name);

/*exit*/
void							ft_exit(t_shell *msh);

/*env*/
void							ft_env(t_shell *msh);

/*unset*/
void							ft_unset(t_shell *msh);

/*cd*/
void							ft_cd(t_shell *msh);
void							add_env(t_env **env, char *name, char *value);

/*pipes*/
int								has_pipes(t_token **tokens);
void							execute_pipes(t_token **tokens, t_shell *msh);

/*pipes_utils*/
int								count_commands(t_token **tokens);
void							setup_child_pipes(int i, int total,
									int pipes[2][2]);
void							close_parent_pipes(int i, int pipes[2][2]);
void							wait_for_children(void);

/*pipes_cmd*/
char							**build_cmd(t_token **tokens, int cmd_idx);

/*pipes_child*/
void							process_pipe_child(t_pipe_data *data);

/*utils_pipes*/
t_token							**get_cmd_tokens(t_pipe_data *data);

/*redirections*/
int								set_infile(t_token **tokens, t_shell *msh,
									char *cmd_name);
int								set_outfile(t_token **tokens, t_shell *msh);
int								set_append_outfile(t_token **tokens,
									t_shell *msh);
void							set_child_hdoc(int hdoc_fd, char *cmd_name);
int								set_redirections(t_token **tokens, t_shell *msh,
									int hdoc_fd);

/*redirections_utils*/
int								is_builtin_redir(char *cmd);
int								handle_ambiguous_redirect(char *filename);
char							*find_command(t_token **tokens);
t_token							*find_redirection_file(t_token **tokens,
									t_token_type redir_type);

/*Utils_global*/
/*env*/
t_env							*find_env(t_env *env_list, char *name);
t_env							*ft_lstnew_env(char *name, char *value,
									int alloc);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
char							*get_env_name(char *fullenv);
char							*get_value_of_env(char *fullenv);

/*free*/
void							ft_free_list(t_env **list);
void							ft_memfree(void *ptr);

/*===========EL INUTIL DE CLAUDIO================*/

// Parser
char							*read_input(void);
char							*get_short_path(void);

t_token							*extract_single_redir_token(char *input,
									int *i);
t_token							*extract_double_redir_token(char *input,
									int *i);
t_token							*extract_pipe_token(char *input, int *i);

void							fill_operator_tokens(char *input,
									t_token **tokens, int *token_count);

int								count_quotes_dob_tokens(char *input);
int								count_quotes_sim_tokens(char *input);
int								count_operator_tokens(char *input);
int								count_word_token(char *input);
t_token							*extract_sim_quote_token(char *input, int *i);
t_token							*extract_dob_quote_token(char *input, int *i);
t_token							*extract_word_token_inline(char *input, int *i);
t_token							**extract_all_tokens(char *input);

// Heredoc
void							heredoc(t_env *env_list, t_token **tokens);
void							msg_ctrld_heredoc(char *to_search);
void							run_heredoc(char *to_search, t_env *env_list,
									t_token *token, int write_fd);
void							exit_heredoc(pid_t pid, int *status);
int								is_valid_heredoc(t_token **tokens, int i);
void							run_heredoc_loop(char *to_search,
									t_env *env_list, t_token *token,
									int write_fd);

// Expansor
t_env							*init_env(char **envp);
char							*get_env_value(t_env *env, char *name);
void							get_value_expanded(char *new_value,
									t_token **tokens, int i, char *env);
void							expand_env_values(t_env *env_list,
									t_token **tokens);
char							*expand_all_vars(t_env *env_list, char *value);
void							add_or_free_token(t_token *token,
									t_token **tokens, int *count);
void							loop_add_tokens(t_token **tmp,
									t_token **tokens, int *index);

// Signals
void							call_signals(void);

#endif
