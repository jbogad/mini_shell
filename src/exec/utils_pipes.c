/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:35:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/13 21:38:48 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Cuenta el número total de comandos separados por pipes
** Ejemplo: "ls | cat | wc" = 3 comandos
*/
int	count_commands(t_token **tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
			count++;
		i++;
	}
	return (count);
}

/*
** Construye el array argv para el comando en la posición cmd_idx
** Ejemplo: en "ls -la | cat", cmd_idx=0 devuelve ["ls", "-la", NULL]
*/
char	**build_cmd(t_token **tokens, int cmd_idx)
{
	char	**argv;
	int		i;
	int		j;
	int		pipes_passed;

	i = 0;
	pipes_passed = 0;
	while (tokens[i] && pipes_passed < cmd_idx)
	{
		if (tokens[i]->type == TOKEN_PIPE)
			pipes_passed++;
		i++;
	}
	j = i;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
		j++;
	argv = malloc(sizeof(char *) * (j - i + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (tokens[i] && tokens[i]->type != TOKEN_PIPE)
		argv[j++] = ft_strdup(tokens[i++]->value);
	argv[j] = NULL;
	return (argv);
}

/*
** Configura las redirecciones de entrada/salida para procesos hijo en pipes
** Conecta STDIN del anterior pipe y STDOUT al siguiente pipe si corresponde
*/
void	setup_child_pipes(int i, int total, int pipes[2][2])
{
	if (i > 0)
	{
		dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
		close(pipes[(i - 1) % 2][0]);
		close(pipes[(i - 1) % 2][1]);
	}
	if (i < total - 1)
	{
		dup2(pipes[i % 2][1], STDOUT_FILENO);
		close(pipes[i % 2][0]);
		close(pipes[i % 2][1]);
	}
}

/*
** Cierra los file descriptors del pipe anterior en el proceso padre
** Evita que queden pipes abiertos innecesariamente
*/
void	close_parent_pipes(int i, int pipes[2][2])
{
	if (i > 0)
	{
		close(pipes[(i - 1) % 2][0]);
		close(pipes[(i - 1) % 2][1]);
	}
}

/*
** Proceso hijo que ejecuta un comando específico en la cadena de pipes
** Configura pipes, construye argv y ejecuta el comando con execvp
*/
void	process_pipe_child(t_token **tokens, int i, int total, int pipes[2][2])
{
	char	**argv;

	argv = build_cmd(tokens, i);
	setup_child_pipes(i, total, pipes);
	if (argv && argv[0] && execvp(argv[0], argv) == -1)
		exit(1);
	exit(1);
}
