/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:25 by clalopez          #+#    #+#             */
/*   Updated: 2025/05/27 15:15:36 by claudio          ###   ########.fr       */
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


//PARSER
char *read_input();

//SIGNALS
void call_signals();



#endif
