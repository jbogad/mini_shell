/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:29:05 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/16 16:10:35 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Muestra un aviso si un heredoc termina por EOF (Ctrl+D).
 * @param to_search Delimitador esperado del heredoc.
 */
void	msg_ctrld_heredoc(char *to_search)
{
	ft_printf("warning: here-document delimited by end-of-file"
		" (wanted `%s')\n",
		to_search);
	free(to_search);
	exit(1);
}

/**
 * @brief Inicia la ejecución de un heredoc.
 *
 * Restaura el manejo por defecto de SIGINT y llama al bucle
 * principal del heredoc.
 *
 * @param to_search Delimitador del heredoc.
 * @param env_list Lista de variables de entorno.
 * @param token Token que contiene el tipo de delimitador.
 * @param write_fd Descriptor de escritura donde se vuelca la entrada.
 */
void	run_heredoc(char *to_search, t_env *env_list, t_token *token,
		int write_fd)
{
	signal(SIGINT, SIG_DFL);
	run_heredoc_loop(to_search, env_list, token, write_fd);
}

/**
 * @brief Espera a que termine el proceso del heredoc.
 *
 * Ignora SIGINT mientras espera, restaura las señales
 * y marca si se debe saltar la siguiente lectura.
 *
 * @param pid PID del proceso heredoc.
 * @param status Estado de salida del proceso.
 */
void	exit_heredoc(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	call_signals();
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_skip_next_readline = 1;
	}
	else if (WIFEXITED(*status) && WEXITSTATUS(*status) == 1)
		g_skip_next_readline = 1;
}

int	is_valid_heredoc(t_token **tokens, int i)
{
	return (tokens[i]->type == TOKEN_HEREDOC && tokens[i + 1]
		&& (tokens[i + 1]->type == TOKEN_WORD
			|| tokens[i + 1]->type == TOKEN_SIM_QUOTE
			|| tokens[i + 1]->type == TOKEN_DOB_QUOTE));
}
