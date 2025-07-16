/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:47:31 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/16 12:29:45 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funciona para contar todos los tokens que hay
 * @param input Línea de entrada a analizar.
 * @return Token extraído si se encuentra, o NULL en caso contrario.
 */
int	count_total_tokens(char *input)
{
	int	ops_tokens;
	int	dob_quotes_tokens;
	int	sim_quotes_tokens;
	int	word_tokens;
	int	total;

	ops_tokens = count_operator_tokens(input);
	dob_quotes_tokens = count_quotes_dob_tokens(input);
	sim_quotes_tokens = count_quotes_sim_tokens(input);
	word_tokens = count_word_token(input);
	total = ops_tokens + dob_quotes_tokens + sim_quotes_tokens + word_tokens;
	return (total);
}

/**
 * @brief Añade tokens de un array temporal a otro array principal.
 * @param tmp Array temporal de tokens para agregar.
 * @param tokens Array principal donde se añaden los tokens.
 * @param index Puntero al índice actual en `tokens`; se incrementa c
 * on cada token añadido.
 */
void	loop_add_tokens(t_token **tmp, t_token **tokens, int *index)
{
	int	j;

	j = 0;
	while (tmp && tmp[j])
	{
		tokens[*index] = tmp[j];
		j++;
		(*index)++;
	}
	free(tmp);
}

/**
 * @brief Obtiene el siguiente token de operador en la entrada.
 * Intenta extraer un token de redirección doble, simple o de pipe, 
 * en ese orden.
 * Avanza el índice `i` según corresponda si se encuentra un token.
 * @param input Cadena de entrada a analizar.
 * @param i Puntero al índice actual en la cadena; se actualiza al 
 * extraer un token.
 * @return El token extraído o NULL si no se encontró ningún token 
 * de operador.
 */
t_token	*get_next_ops_token(char *input, int *i)
{
	t_token	*token;

	token = extract_double_redir_token(input, i);
	if (token != NULL)
		return (token);
	token = extract_single_redir_token(input, i);
	if (token != NULL)
		return (token);
	token = extract_pipe_token(input, i);
	if (token != NULL)
		return (token);
	return (NULL);
}

t_token	*get_next_token(char *input, int *i)
{
	t_token	*token;

	token = get_next_ops_token(input, i);
	if (token != NULL)
		return (token);
	if (input[*i] == '\'')
	{
		token = extract_sim_quote_token(input, i);
		if (token != NULL)
			return (token);
	}
	if (input[*i] == '"')
	{
		token = extract_dob_quote_token(input, i);
		if (token != NULL)
			return (token);
	}
	token = extract_word_token_inline(input, i);
	if (token != NULL)
		return (token);
	(*i)++;
	return (NULL);
}


/*============================================================*/


/*PARA MI EL ERROR ESTA AQUI, CON LA FUNCIÓN DE ABAJO SI QUE 
FUNCIONAN LAS DOBLES COMILLAS Y LAS SIMPLES*/












/**
 * @brief Extrae todos los tokens de la cadena de entrada.
 * Recorre la cadena `input`, saltando espacios y tabulaciones, 
 * y extrae tokens usando `get_next_token`.
 * @param input Cadena de entrada a tokenizar.
 * @return Arreglo terminado en NULL con todos los tokens extraídos,
 *  o NULL en error.
 */
// t_token	**extract_all_tokens(char *input)
// {
// 	t_token	**tokens;
// 	t_token	*token;
// 	int		i;
// 	int		token_count;
// 	int		len;

// 	i = 0;
// 	token_count = 0;
// 	len = ft_strlen(input);
// 	tokens = malloc(sizeof(t_token *) * (len + 1));
// 	if (!tokens)
// 		return (NULL);
// 	while (input[i])
// 	{
// 		while (input[i] == ' ' || input[i] == '\t')
// 			i++;
// 		if (!input[i])
// 			break ;
// 		token = get_next_token(input, &i);
// 		if (token)
// 			tokens[token_count++] = token;
// 	}
// 	tokens[token_count] = NULL;
// 	return (tokens);
// }

t_token	**extract_all_tokens(char *input)
{
    t_token	**tokens;
    t_token	*token;
    int		vars[3];

    vars[0] = 0;
    vars[1] = 0;
    vars[2] = ft_strlen(input);
    tokens = malloc(sizeof(t_token *) * (vars[2] + 1));
    if (!tokens)
        return (NULL);
    while (input[vars[0]])
    {
        while (input[vars[0]] == ' ' || input[vars[0]] == '\t')
            vars[0]++;
        if (!input[vars[0]])
            break ;
        token = get_next_token(input, &vars[0]);
        if (!token)
        {
            free(tokens);
            return (NULL);
        }
        if (token->value && token->value[0] != '\0')
            tokens[vars[1]++] = token;
        else
            free(token->value), free(token);
    }
    tokens[vars[1]] = NULL;
    return (tokens);
}

