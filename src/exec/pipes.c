/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:05:47 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/13 21:38:48 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Verifica si hay pipes (|) en la lista de tokens
** Devuelve 1 si encuentra al menos un pipe, 0 si no
*/
int	has_pipes(t_token **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
			return (1);
		i++;
	}
	return (0);
}

/*
** Ejecuta una cadena de comandos conectados por pipes
** Crea procesos hijo para cada comando y conecta sus entrada/salida
*/
void	execute_pipes(t_token **tokens, t_shell *msh)
{
	int		pipes[2][2];
	int		i;
	int		total;
	pid_t	pid;

	(void)msh;
	total = count_commands(tokens);
	i = 0;
	while (i < total)
	{
		if (i < total - 1 && pipe(pipes[i % 2]) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			process_pipe_child(tokens, i, total, pipes);
		if (pid > 0)
			close_parent_pipes(i, pipes);
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
}
