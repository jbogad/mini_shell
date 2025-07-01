/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:31:07 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

/*
	PARTE DE JAVIER
	main inicia las variables de entorno que las guarda en una lista t_env
	con valor de la variable y nombre de la variable.
	Genera la shell
	extrae los tokerns en una lista t_token depende del tipo de token que sea
	trata los heredoc << pero antes de ejecutar
	mi parte de ejecutro donde busca el comando
	libera los tokens y la entrada en cada iteracion del bucle
*/

extern volatile sig_atomic_t	g_skip_next_readline;

/**
 * @brief Esto simplemente comprueba que solo se ejecute ./minishell
 * Y abre la minishell
 */
char	*gen_shell(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (read_input());
}
/*Main para probar que se genera la shell y que la call_signals
funcionan*/
/*Main para probar pwd y creo que funciona bien(javier)*/
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	**tokens_ext;
	t_env	*env_list;

	env_list = init_env(envp);
	call_signals();

	while (1)
	{
		//Esto es para evitar que haya doble prompt
		if (g_skip_next_readline)
		{
			g_skip_next_readline = 0;
			continue;
		}

		input = gen_shell(argc, argv);
		if (!input)
		{
			ft_printf("exit\n");
			rl_clear_history();
			break ;
		}

		if (*input)
		{
			tokens_ext = extract_all_tokens(input);

			//Procesar heredocs ANTES de ejecutar comandos
			heredoc(env_list, tokens_ext);

			if (!g_skip_next_readline && tokens_ext && tokens_ext[0])
				execute(tokens_ext);
				
			int i = 0;
			ft_printf("=== TOKENS ===\n");
			while (tokens_ext && tokens_ext[i])
			{
			ft_printf("Token[%d]: type=%d, value=%s\n", i, tokens_ext[i]->type, tokens_ext[i]->value);
				i++;
			}
			ft_printf("====================\n");

			i = 0;
			while (tokens_ext && tokens_ext[i])
			{
				free(tokens_ext[i]->value);
				free(tokens_ext[i]);
				i++;
			}


			free(tokens_ext);
		}
		free(input);
	}
	free_env(env_list);
	return (0);
}




// int main(int argc, char **argv)
// {
// 	char	*input;
// 	t_token	token[10];
// 	t_token	*tokens[11];
// 	char	**args;
// 	int		i;

// 	call_signals();
// 	while (1)
// 	{
// 		input = gen_shell(argc, argv);
// 		if	(!input)
// 		{
// 			ft_printf("exit\n");
// 			rl_clear_history();
// 			break ;
// 		}
// 		if (*input)
// 		{
// 			args = ft_split(input, ' ');
// 			i = 0;
// 			while (args[i] && i < 10)
// 			{
// 				token[i].type = TOKEN_WORD;
// 				token[i].value = args[i];
// 				tokens[i] = &token[i];
// 				i++;
// 			}
// 			tokens[i] = NULL;
// 			execute(tokens);
// 			free(args);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }