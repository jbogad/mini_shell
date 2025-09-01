/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:05:47 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/01 11:10:30 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Valida la sintaxis de pipes en los tokens
** Devuelve 0 si hay errores de sintaxis, 1 si es válido
*/
static int	validate_pipe_syntax(t_token **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (1);
	if (tokens[0]->type == TOKEN_PIPE)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
		{
			if (!tokens[i + 1] || tokens[i + 1]->type == TOKEN_PIPE)
				return (0);
		}
		i++;
	}
	return (1);
}

/*
** Verifica si hay pipes (|) en la lista de tokens
** Devuelve 1 si encuentra al menos un pipe, 0 si no
*/
int	has_pipes(t_token **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	if (!validate_pipe_syntax(tokens))
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
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

	total = count_commands(tokens);
	i = 0;
	while (i < total)
	{
		if (i < total - 1 && pipe(pipes[i % 2]) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			process_pipe_child(tokens, i, total, pipes, msh);
		if (pid > 0)
			close_parent_pipes(i, pipes);
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
}
