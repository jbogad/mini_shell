/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/02 14:29:24 by jaboga-d         ###   ########.fr       */
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
int	main(int argc, char **argv)
{
	char *input;
	t_token token;
	t_token *tokens[2]; // guardo la lista de tokens , tengo que cambiarla

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

		ft_printf("Input: %s\n", input);
		int sim_quotes = count_quotes_sim_tokens(input);
		ft_printf("Tokens comillas sim: %d\n", sim_quotes);

		/* t_token **tokens_word = extract_word_token(input);
		int i = 0;
		while (tokens_word[i] != NULL)
		{
            ft_printf("[Token de tipo %d]: Valor:%s\n", tokens_word[i]->type, tokens_word[i]->value);
			i++;
		} */  
	}
	return (0);
}