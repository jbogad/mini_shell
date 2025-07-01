/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:07:24 by claudio           #+#    #+#             */
/*   Updated: 2025/07/01 12:27:14 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funcion para manejar la señal cuando se haga ctrl+c
 * Salta a una nueva linea, la inicia vacia.
 * Redisplay hace que el prompt de readline se mantenga(minishell$)
 */
void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Esta funcion hace que cuando se haga ctrl+c(SIGINT), 
 * llame y haga la funcion signal_handler()git 
 */
void	ctrl_c(void)
{
	signal(SIGINT, signal_handler);
}

/**
 * @brief Esta funcion hace que cuando se haga ctrl+/(SIGQUIT), 
 * no  haga nada. Esto creo que no sirve para nada
 */
void	ctrl_backslash(void)
{
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Esta funcion simplemente es para llamar a las señales
 * y ahorrarse alguna linea de codigo
 */
void	call_signals(void)
{
	ctrl_c();
	ctrl_backslash();
}
