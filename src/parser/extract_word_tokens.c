/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:23:09 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:20:47 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funcion para identificar los token_word y contar cuantos hay
 * @param input La linea que se lee al ejecutar el readline
 * @return Devuelve la cantidad de token_word que hay
 */
int	count_word_token(char *input)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '<' && input[i] != '>'
			&& input[i] != '|')
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (count);
}

/**
 * @brief Funcion para ir añadiendo los tokens
 * @param tokens Estructura de los tokens
 * @param input La linea que se lee al ejecutar el readline
 * @param start Saber em que parte deñ input empieza
 * @param token_count Contador de tokens
 */
void	add_word_token(t_token **tokens, char *input, int start,
		int *token_count)
{
	t_token	*new_token;
	int		end;

	end = start;
	while (input[end] && input[end] != ' ' && input[end] != '|'
		&& input[end] != '>' && input[end] != '<')
		end++;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = TOKEN_WORD;
	new_token->value = ft_strndup(&input[start], end - start);
	tokens[(*token_count)++] = new_token;
}

/**
 * @brief Funcion para saltar los espacion y comillas
 * @param input La linea que se lee al ejecutar el readline
 * @param i Contador
 * @return Devuelve la cantidad de espacios y comillas
 */
int	skip_spaces_and_quotes(char *input, int i)
{
	if (!input)
		return (i);
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

/**
 * @brief Extrae tokens de tipo palabra desde el input.
 * Recorre la línea de entrada y crea una lista de tokens de tipo palabra
 * (TOKEN_WORD), ignorando espacios y caracteres especiales como pipes o 
 * redirecciones.
 * @param input La línea leída con readline.
 * @return Lista de tokens extraídos, terminada en NULL.
 */

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
	while (input && input[i])
	{
		i = skip_spaces_and_quotes(input, i);
		start = i;
		while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>'
			&& input[i] != '<')
			i++;
		if (start != i)
			add_word_token(tokens, input, start, &token_count);
		else if (input[i])
			i++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}

/**
 * @brief Extrae un token de tipo palabra desde la posición actual del input.
 * Lee caracteres hasta encontrar un espacio, redirección, pipe o comillas.
 * Devuelve un token con el contenido leído y actualiza el índice.
 * @param input Línea de entrada.
 * @param i Puntero al índice actual dentro del input.
 * @return Token de tipo palabra o NULL si no se encontró nada.
 */
t_token	*extract_word_token_inline(char *input, int *i)
{
	int		start;
	t_token	*token;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '|'
		&& input[*i] != '\'' && input[*i] != '"')
	{
		(*i)++;
	}
	if (start == *i)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_WORD;
	token->value = ft_strndup(&input[start], *i - start);
	return (token);
}
