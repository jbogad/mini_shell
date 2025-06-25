/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:15:45 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/25 16:52:37 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile sig_atomic_t	g_skip_next_readline = 0;

//Funcion para correr el heredoc hasta que se haga ctrl+d
//o se encuntre la palabra, tb  expande los tokens  de tipo word como en bash para 
//cuando se hace por ejemplo con un cat (cat << hola)
void	run_heredoc_loop(char *to_search, t_env *env_list, t_token *token)
{
	char	*her_input;
	char	*expanded;

	her_input = NULL;
	//Bucle para hacer el heredoc hasta que se haga ctrl+d o se encuentre la palabra
	while (1)
	{
		free(her_input);
		her_input = readline("> ");
		if (!her_input)
		{
			ft_printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
				to_search);
			free(to_search);
			exit(1);
		}
		if (ft_strcmp(her_input, to_search) == 0)
			break ;
		if (token->type == TOKEN_WORD)
		{
			expanded = expand_all_vars(env_list, her_input);
			free(her_input);
			her_input = expanded;
		}
	}
	free(her_input);
	free(to_search);
	exit(0);
}

//Funcion para recorrer los tokens hasta que se encuentre un tipo | y 
//lo siguiente sea palabra o entre comillas, asigna la palabra y hace
//el loop
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
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				run_heredoc_loop(to_search, env_list, tokens[i + 1]);
			}
			else
			{
				signal(SIGINT, SIG_IGN);//Ignora  el ctrl+c de la minishell
				waitpid(pid, &status, 0);//Espera al heredoc
				call_signals();
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				{
					write(STDOUT_FILENO, "\n", 1);
					g_skip_next_readline = 1; //Saltar al siguiente readline si se hace ctr+c
				}
				else if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
					g_skip_next_readline = 1; //Saltar al siguiente readline si se hace ctr+d
			}
			free(to_search);
			i++;
		}
		i++;
	}
}
