/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:07:24 by claudio           #+#    #+#             */
/*   Updated: 2025/06/06 15:08:39 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Funcion para manejar la señal cuando se haga ctrl+call_signal
Salta a una nueva linea, la inicia vacia.
Redisplay hace que el prompt de readline se mantenga(minishell$)*/
void	signal_handler()
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	ctrl_c()
{
	signal(SIGINT, signal_handler);
}

void	ctrl_backslash()
{
	signal(SIGQUIT, SIG_IGN);
}

void	call_signals()
{
	ctrl_c();
	ctrl_backslash();
}
