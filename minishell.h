/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:25 by clalopez          #+#    #+#             */
/*   Updated: 2025/05/28 19:56:39 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "src/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Estructura para guardar los tokens del input
cada token tendra su valor guardado 
ej: TOKEN_WORD -> echo */
typedef enum e_token_type
{
    TOKEN_WORD,       // comandos y argumntos
    TOKEN_PIPE,       // |
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_APPEND,     // >>
    TOKEN_HEREDOC,    // <<
    TOKEN_STRING,     // string entre comillas
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char         *value;
} t_token;



/*================JAVIER================*/

/*pwd*/
void    ft_pwd(void);

/*exec*/
void execute(t_token **tokens);


/*===========EL INUTIL DE CLAUDIO================*/

//PARSER
char *read_input();
char	*get_short_path(void);

//SIGNALS
void call_signals();



#endif
