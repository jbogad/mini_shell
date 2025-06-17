/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/17 15:32:22 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Funcion para comprobar que solo se ejcuta el ejecutable
y generar la shell con el read_input*/
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
	t_token	token;
	t_env	*env_list;
	t_token	**tokens_ext;
	int		i;

	t_token *tokens[2]; // guardo la lista de tokens , tengo que cambiarla
	env_list = init_env(envp);
	call_signals();
	while (1)
	{
		input = gen_shell(argc, argv);
		if (!input)
		{
			ft_printf("exit\n");
			rl_clear_history();
			break ;
		}
		/*parte de javier para probar comandos, asigno el tipo de dato
		le doy el comando al value "pwd" meto la memoria y luego null y ejecuto*/
		if (*input)
		{
			token.type = TOKEN_WORD;
			token.value = input;
			tokens[0] = &token;
			tokens[1] = NULL;
			execute(tokens);
		}

		//Claudio, esto es solo pruebas
		ft_printf("Input: %s\n", input);
		tokens_ext = extract_all_tokens(input);
		expand_env_values(env_list, tokens_ext);
		i = 0;
		while (tokens_ext[i] != NULL)
		{
			ft_printf("[Token de tipo %d]: Valor:%s\n", tokens_ext[i]->type,
				tokens_ext[i]->value);
			free(tokens_ext[i]->value);
			free(tokens_ext[i]);
			i++;
		}
		free(tokens_ext);
		free(input);
		// free_tokens(tokens_ext);
	}
	free_env(env_list);
	free(input);
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