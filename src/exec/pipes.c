/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:05:47 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/04 10:51:08 by jbogad           ###   ########.fr       */
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
		printf("minishell: syntax error near unexpected token `|'\n");
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

static void	setup_pipe_data(t_pipe_data *data, t_token **tokens,
		int i, t_shell *msh)
{
	data->tokens = tokens;
	data->cmd_idx = i;
	data->msh = msh;
}

static void	handle_child_process(t_pipe_data *data, int pipes[2][2])
{
	ft_memcpy(data->pipes, pipes, 2 * 2 * sizeof (int));
	process_pipe_child(data);
}

/*
** Ejecuta una cadena de comandos conectados por pipes
** Crea procesos hijo para cada comando y conecta sus entrada/salida
*/
void	execute_pipes(t_token **tokens, t_shell *msh)
{
	int			pipes[2][2];
	int			i;
	int			total;
	pid_t		pid;
	t_pipe_data	data;

	total = count_commands(tokens);
	i = 0;
	while (i < total)
	{
		if (i < total - 1 && pipe(pipes[i % 2]) == -1)
			return ;
		pid = fork();
		if (pid == 0)
		{
			setup_pipe_data(&data, tokens, i, msh);
			data.total = total;
			handle_child_process(&data, pipes);
		}
		if (pid > 0)
			close_parent_pipes(i, pipes);
		i++;
	}
	wait_for_children();
}
