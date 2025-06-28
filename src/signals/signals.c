/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:07:24 by claudio           #+#    #+#             */
/*   Updated: 2025/06/28 16:36:04 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Funcion para manejar la señal cuando se haga ctrl+c
Salta a una nueva linea, la inicia vacia.
Redisplay hace que el prompt de readline se mantenga(minishell$)*/
void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c(void)
{
	signal(SIGINT, signal_handler);
}

void	ctrl_backslash(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	call_signals(void)
{
	ctrl_c();
	ctrl_backslash();
}
