/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ops_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:51:27 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:21:44 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funcion para identificar los tokens ops(< << > >> |) y 
 * contar cuantos hay
 * @param input La linea que se lee al ejecutar el readline
 * @return Devuelve la cantidad de tokens ops que hay
 */
int	count_operator_tokens(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if ((input[i] == '<' && input[i + 1] && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] && input[i + 1] == '>'))
		{
			count++;
			i += 2;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

/**
 * @brief Extrae un token de tipo pipe (|) del input.
 * Si el carácter actual es un '|', crea un nuevo token
 * con ese valor y actualiza el índice.
 * @param input Línea de entrada.
 * @param i Puntero al índice actual en la línea; se incrementa si se 
 * extrae un token.
 * @return Un nuevo token de tipo TOKEN_PIPE o NULL si no se encuentra '|'.
 */
t_token	*extract_pipe_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '|')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_PIPE;
		new_token->value = ft_strdup("|");
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
		(*i)++;
		return (new_token);
	}
	return (NULL);
}

/**
 * @brief Extrae un token de doble redirección ('<<' o '>>') del input.
 * Detecta si hay un '<<' (heredoc) o '>>' (append),
	crea un token correspondiente,
 * y avanza el índice en 2 posiciones.
 * @param input Línea de entrada.
 * @param i Puntero al índice actual en la línea; se incrementa si se 
	extrae un token.
 * @return Un nuevo token de tipo TOKEN_HEREDOC o TOKEN_APPEND,
	o NULL si no se encuentra ninguno.
 */
t_token	*extract_double_redir_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_HEREDOC;
		new_token->value = ft_strdup("<<");
		(*i) += 2;
		return (new_token);
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_APPEND;
		new_token->value = ft_strdup(">>");
		(*i) += 2;
		return (new_token);
	}
	return (NULL);
}

/**
 * @brief Extrae un token de doble redirección ('<' o '>') del input.
 * Detecta si hay un '<' (redir_in) o '>' (redir_out),
	crea un token correspondiente,
 * y avanza el índice en 2 posiciones.
 * @param input Línea de entrada.
 * @param i Puntero al índice actual en la línea; se incrementa si se 
 * extrae un token.
 * @return Un nuevo token de tipo TOKEN_REDIR_IN o TOKEN_REDIR_OUT,
	o NULL si no se encuentra ninguno.
 */
t_token	*extract_single_redir_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '<')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_REDIR_IN;
		new_token->value = ft_strdup("<");
		(*i)++;
		return (new_token);
	}
	else if (input[*i] == '>')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_REDIR_OUT;
		new_token->value = ft_strdup(">");
		(*i)++;
		return (new_token);
	}
	return (NULL);
}

/**
 * @brief Extrae todos los tokens de operadores del input ('<', '>', 
 * '<<', '>>', '|').
 * Reserva memoria para los tokens, cuenta cuántos operadores hay y los llena
 * en la lista usando la función fill_operator_tokens.
 * @param input Línea de entrada del usuario.
 * @return Lista de tokens de operadores,
	terminada en NULL. Devuelve NULL si falla la memoria.
 */
t_token	**extract_ops_tokens(char *input)
{
	t_token	**tokens;
	int		token_count;

	token_count = 0;
	tokens = malloc(sizeof(t_token *) * (count_operator_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	fill_operator_tokens(input, tokens, &token_count);
	tokens[token_count] = NULL;
	return (tokens);
}
