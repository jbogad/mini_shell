/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_dob_tokens.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:15 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/16 10:30:08 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funcion para identificar los token_dob_quote y contar cuantos hay
 * @param input La linea que se lee al ejecutar el readline
 * @return Devuelve la cantidad de token_dob_quote que hay
 */
int	count_quotes_dob_tokens(char *input)
{
	int	i;
	int	count;
	int	in_double_quote;
	int	in_single_quote;

	i = 0;
	count = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (input[i++])
	{
		if (input[i - 1] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i - 1] == '"' && !in_single_quote)
		{
			if (in_double_quote)
			{
				in_double_quote = 0;
				count++;
			}
			else
				in_double_quote = 1;
		}
	}
	return (count);
}

/**
 * @brief Funcion para inicializar la estructura de extraccion de comillas
 * @param e La estructura de extraccion de las comillas
 */
void	init_extract2(t_extract *e)
{
	e->i = 0;
	e->start = -1;
	e->count = 0;
	e->in_sim_quote = 0;
	e->in_dob_quote = 0;
}

/**
 * @brief Extrae tokens entre comillas dobles del input.
 * Recorre la línea de entrada y guarda en tokens los fragmentos
 * entre comillas dobles, siempre que no estén dentro de comillas simples.
 * @param input La línea leída.
 * @param tokens Lista donde se almacenan los tokens encontrados.
 * @param e Estructura auxiliar.
 */
void	fill_dob_quote_tokens(char *input, t_token **tokens, t_extract *e)
{
	t_token	*new_tkn;

	init_extract2(e);
	while (input[e->i])
	{
		if (input[e->i] == '\'' && !e->in_dob_quote)
			e->in_sim_quote = !e->in_sim_quote;
		else if (input[e->i] == '"' && !e->in_sim_quote)
		{
			if (e->in_dob_quote)
			{
				e->in_dob_quote = 0;
				new_tkn = malloc(sizeof(t_token));
				new_tkn->type = TOKEN_DOB_QUOTE;
				new_tkn->value = ft_strndup(&input[e->start], e->i - e->start);
				tokens[e->count++] = new_tkn;
			}
			else
			{
				e->start = e->i + 1;
				e->in_dob_quote = 1;
			}
		}
		e->i++;
	}
}

/**
 * @brief Extrae un token entre comillas dobles desde la posición dada.
 * Busca la próxima comilla doble desde la posición actual en el input
 * y crea un token con el texto entre esas comillas.
 * @param input Línea de entrada.
 * @param i Puntero al índice actual que se irá actualizando.
 * @return Token de tipo TOKEN_DOB_QUOTE o NULL si hay error o no se cierra
 * la comilla.
 */
t_token	*extract_dob_quote_token(char *input, int *i)
{
	t_token	*token;
	int		start;
	char	*before;
	char	*inside;
	int		quote_start;

	start = *i;
	while (start > 0 && input[start - 1] != ' ' && input[start - 1] != '\t'
		&& input[start - 1] != '|' && input[start - 1] != '<' && input[start
			- 1] != '>')
		start--;
	before = ft_strndup(input + start, *i - start);
	quote_start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	inside = ft_strndup(input + quote_start, *i - quote_start);
	token = malloc(sizeof(t_token));
	token->type = TOKEN_DOB_QUOTE;
	token->value = ft_strjoin(before, inside);
	free(before);
	free(inside);
	(*i)++;
	return (token);
}
