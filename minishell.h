/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:25 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/06 14:59:06 by jaboga-d         ###   ########.fr       */

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
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/* Estructura para guardar los tokens del input
cada token tendra su valor guardado
ej: TOKEN_WORD -> echo */
typedef enum e_token_type
{
	TOKEN_WORD,			// comandos y argumntos
	TOKEN_PIPE,			// |
	TOKEN_REDIR_IN,		// <
	TOKEN_REDIR_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_SIM_QUOTE,	// string entre comillas simples 'Hola'
	TOKEN_DOB_QUOTE,	// string entre comillas doblres "Ho la"
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_extract
{
	int				i;
	int				start;
	int				count;
	int				index;
	int				in_sim_quote;
	int				in_dob_quote;
}					t_extract;

typedef struct s_env
{
	char	*name_env;
	char	*val_env;
	struct s_env *next;
}				t_env;

// Utils
char				*ft_strndup(const char *s, size_t n);
void				free_tokens(t_token **tokens);

/*================JAVIER================*/

/*pwd*/
void				ft_pwd(void);

/*echo*/
void				ft_echo(t_token **tokens);

/*cd*/
void				ft_cd(t_token **tokens);

/*exec*/
void				execute(t_token **tokens);

/*===========EL INUTIL DE CLAUDIO================*/

// Parser
char				*read_input(void);
char				*get_short_path(void);

t_token	*extract_single_redir_token(char *input, int *i);
t_token	*extract_double_redir_token(char *input, int *i);
t_token	*extract_pipe_token(char *input, int *i);


void				fill_operator_tokens(char *input, t_token **tokens,
						int *token_count);

int					count_quotes_dob_tokens(char *input);
int					count_quotes_sim_tokens(char *input);
int					count_operator_tokens(char *input);
int					count_word_token(char *input);
t_token				**extract_word_token(char *input);
t_token				**extract_ops_tokens(char *input);
t_token				**extract_dob_quote_tokens(char *input);
t_token				**extract_sim_quote_tokens(char *input);
t_token				**extract_all_tokens(char *input);

// Signals
void				call_signals(void);

#endif
