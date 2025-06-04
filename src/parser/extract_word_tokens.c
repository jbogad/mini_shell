/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:23:09 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/04 16:07:48 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Funcion para contar cuantos tokens_word hay
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

// Funciones para dividir el input en tokens
// IMPORTANTE: No interpretar comillas sin cerrar o caracteres 
//especiales no especificados en el
// enunciado como \ (barra invertida) o ; (punto y coma).
// No se si tiene que mostrar error o se la tiene que pelar
int	skip_spaces_and_quotes(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	if (input[i] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i] == '\'')
			i++;
	}
	if (input[i] == '"')
	{
		i++;
		while (input[i] && input[i] != '"')
			i++;
		if (input[i] == '"')
			i++;
	}
	return (i);
}

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
		i = skip_spaces_and_quotes(input, i);
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
