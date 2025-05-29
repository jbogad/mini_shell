/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:23:09 by clalopez          #+#    #+#             */
/*   Updated: 2025/05/29 15:39:51 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Funcion para contar cuantos tokens_word hay
int	count_word_token(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == ' ' && input[i + 1] != ' ' && input[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}
// Funcion para ir añadiendo los tokens, tengo que quitarle un parametro  
void	add_word_token(t_token **tokens, char *input, int start, int end,
		int *token_count)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = TOKEN_WORD;
	new_token->value = ft_strndup(&input[start], end - start);
	tokens[*token_count] = new_token;
	(*token_count)++;
}
// Funcion para dividir el input en tokens
// IMPORTANTE: No interpretar comillas sin cerrar o caracteres especiales no especificados en el
// enunciado como \ (barra invertida) o ; (punto y coma).
// No se si tiene que mostrar error o se la tiene que pelar
t_token	**extract_word_token(char *input)
{
	int		i;
	int		start;
	t_token	**tokens;
	int		token_count;

	i = 0;
	token_count = 0;
	tokens = malloc(sizeof(t_token *) * (count_word_token(input) + 1));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		start = i;
		while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>'
			&& input[i] != '<')
			i++;
		if (start != i)
			add_word_token(tokens, input, start, i, &token_count);
		else
			i++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
// Esto es para ver que se divide en tokens(Claudio)
// Si lo quieres probar ponlo debajo de tu if en el main
		/* ft_printf("Input: %s\n", input);
		t_token **tokens_word = extract_word_token(input);
		int i = 0;
		while (tokens_word[i] != NULL)
		{
            ft_printf("[Token de tipo %d]: Valor:%s\n", tokens_word[i]->type, tokens_word[i]->value);
			i++;
		} */

