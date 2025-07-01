/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ops_tokens_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:19:12 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:18:13 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Intenta extraer un token de operador del input.
 * Comprueba si el carácter actual es un pipe ('|'),
	redirección doble ('<<' o '>>')
 * o redirección simple ('<' o '>'), y devuelve el token correspondiente.
 * @param input Línea de entrada a analizar.
 * @param i Puntero al índice actual dentro del input. Se actualiza si 
 * se encuentra un token.
 * @return Token extraído si se encuentra, o NULL en caso contrario.
 */
t_token	*get_operator_token(char *input, int *i)
{
	t_token	*token;

	token = extract_pipe_token(input, i);
	if (!token)
		token = extract_double_redir_token(input, i);
	if (!token)
		token = extract_single_redir_token(input, i);
	return (token);
}

/**
 * @brief Llena el array de tokens con los operadores encontrados en el input.
 * Recorre la línea de entrada,
	ignorando operadores dentro de comillas simples o dobles,
 * y extrae los tokens de operadores (`|`, `>`, `>>`, `<`, `<<`) que encuentra.
 * @param input Línea de entrada a analizar.
 * @param tokens Array donde se almacenarán los tokens extraídos.
 * @param token_count Puntero al número actual de tokens; se incrementa con 
	cada nuevo token.
 */
void	fill_operator_tokens(char *input, t_token **tokens, int *token_count)
{
	int		i;
	int		in_squote;
	int		in_dquote;
	t_token	*token;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		if (!in_squote && !in_dquote)
		{
			token = get_operator_token(input, &i);
			if (token)
			{
				tokens[(*token_count)++] = token;
				continue ;
			}
		}
		i++;
	}
}
