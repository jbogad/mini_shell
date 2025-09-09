/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:15:45 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/09 11:48:36 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile sig_atomic_t	g_skip_next_readline = 0;

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
 * @brief Ejecuta el bucle principal de un heredoc.
 *
 * Lee líneas del usuario hasta que se introduzca el delimitador
 * o se reciba EOF (Ctrl+D). Si el delimitador no está entre comillas,
 * expande las variables de entorno. Escribe la entrada resultante en
 * el descriptor de escritura y luego termina el proceso.
 *
 * @param to_search Delimitador del heredoc.
 * @param env_list Lista de variables de entorno.
 * @param token Token que contiene el tipo de delimitador (citado o no).
 * @param write_fd Descriptor de escritura donde se vuelca la entrada.
 */
void	run_heredoc_loop(char *to_search, t_env *env_list, t_token *token,
		int write_fd)
{
	char	*her_input;
	char	*expanded;
	int		quoted;

	her_input = NULL;
	quoted = (token->type == TOKEN_SIM_QUOTE || token->type == TOKEN_DOB_QUOTE);
	while (1)
	{
		free(her_input);
		her_input = readline("> ");
		if (!her_input)
			msg_ctrld_heredoc(ft_strdup(to_search));
		if (ft_strcmp(her_input, to_search) == 0)
			break ;
		if (!quoted && token->type == TOKEN_WORD)
		{
			expanded = expand_all_vars(env_list, her_input);
			free(her_input);
			her_input = expanded;
		}
		write(write_fd, her_input, ft_strlen(her_input));
		write(write_fd, "\n", 1);
	}
	free(her_input);
	close(write_fd);
	exit(0);
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

/**
 * @brief Gestiona todos los heredocs en la lista de tokens.
 *
 * Recorre los tokens buscando operadores heredoc (<<).
 * Cuando encuentra uno, crea un pipe y un proceso hijo para
 * leer la entrada del heredoc. El padre espera al hijo y
 * guarda el descriptor en el token correspondiente.
 *
 * @param env_list Lista de variables de entorno.
 * @param tokens Lista de tokens del comando.
 */
void	heredoc(t_env *env_list, t_token **tokens)
{
	int		i;
	char	*to_search;
	pid_t	pid;
	int		status;
	int		fd[2];

	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i]->type == TOKEN_HEREDOC && tokens[i + 1] && (tokens[i
				+ 1]->type == TOKEN_WORD || tokens[i
				+ 1]->type == TOKEN_SIM_QUOTE || tokens[i
				+ 1]->type == TOKEN_DOB_QUOTE))
		{
			to_search = ft_strdup(tokens[i + 1]->value);
			if (pipe(fd) == -1)
			{
				perror("pipe");
				free(to_search);
				return ;
			}
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				signal(SIGINT, SIG_DFL);
				run_heredoc_loop(to_search, env_list, tokens[i + 1], fd[1]);
				exit(0);
			}
			else if (pid > 0)
			{
				close(fd[1]);
				exit_heredoc(pid, &status);
				if (!g_skip_next_readline)
				{
					if (i > 0)
						tokens[i - 1]->heredoc_fd = fd[0];
					else
						close(fd[0]);
				}
				else
					close(fd[0]);
			}
			else
			{
				perror("fork");
				free(to_search);
				return ;
			}
			free(to_search);
			i += 2;
			continue ;
		}
		i++;
	}
}
