/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:15:45 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:07 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile sig_atomic_t	g_skip_next_readline = 0;

/**
 * @brief Funcion para mostrar el mensaje fr warning de bash
 * @param to_search caracter a encontrar
 */
void	msg_ctrld_heredoc(char *to_search)
{
	ft_printf("warning: here-document delimited by end-of-file"
		"(wanted `%s')\n", to_search);
	free(to_search);
	exit(1);
}

/**
 * @brief Funcion para correr el heredoc hasta que sea nulo(ctrl+d)
 * o se encuntre la palabra, tb  expande los tokens  de tipo
 * word como en bash para cuando se hace por ejemplo con
 * un cat (cat << hola)
 * @param to_search Caracter a encontrar
 * @param env_list Lista de las variable globales del env con nombre y vaolr.
 * @param token Estructura de los tokens
 */
void	run_heredoc_loop(char *to_search, t_env *env_list, t_token *token)
{
	char	*her_input;
	char	*expanded;

	her_input = NULL;
	while (1)
	{
		free(her_input);
		her_input = readline("> ");
		if (!her_input)
			msg_ctrld_heredoc(to_search);
		if (ft_strcmp(her_input, to_search) == 0)
			break ;
		if (token->type == TOKEN_WORD)
		{
			expanded = expand_all_vars(env_list, her_input);
			free(her_input);
			her_input = expanded;
		}
		ft_printf("Input: %s\n", her_input);
	}
	free(her_input);
	free(to_search);
	exit(0);
}

void	run_heredoc(char *to_search, t_env *env_list, t_token *next_token)
{
	signal(SIGINT, SIG_DFL);
	run_heredoc_loop(to_search, env_list, next_token);
}

/**
 * @brief Espera a que acabe el proceso hijo encargado del heredoc.
 * Esta función se encarga de esperar al proceso hijo que ejecuta el heredoc
 * gestionando las señales. Ignora ctrl+c mientras 
 * espera, y después restaura las señales de la minishell. 
 * Si el heredoc termina con ctrl+c o ctrl+d actualiza la variable global
 * para decirle que ahora esta en la parte de minishell y no heredoc
 * @param pid pid del proceso hijo que está ejecutando el heredoc
 * @param status puntero a la variable donde se guardara el codigo de salida
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
 * @brief Esta funcion recorre los tokens y si encuentra un heredoc seguido
 * de comillas o palabra, empieza a correr el heredoc
 * @param env_list Lista de las variable globales del env con nombre y vaolr.
 * @param token Estructura de los tokens
 */
void	heredoc(t_env *env_list, t_token **tokens)
{
	int		i;
	char	*to_search;
	pid_t	pid;
	int		status;

	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i]->type == TOKEN_HEREDOC && tokens[i + 1] && (tokens[i
					+ 1]->type == TOKEN_WORD || tokens[i
					+ 1]->type == TOKEN_SIM_QUOTE || tokens[i
					+ 1]->type == TOKEN_DOB_QUOTE))
		{
			to_search = ft_strdup(tokens[i + 1]->value);
			ft_printf("A BUSCAR: %s\n", to_search);
			pid = fork();
			if (pid == 0)
				run_heredoc(to_search, env_list, tokens[i + 1]);
			else
				exit_heredoc(pid, &status);
			free(to_search);
			i++;
		}
		i++;
	}
}
