/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_dob_tokens.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:15 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/28 11:58:29 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Contar cuantos tokens de dobles comillas hay
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

// Inicializar las variables para extraer los tokens
void	init_extract2(t_extract *e)
{
	e->i = 0;
	e->start = -1;
	e->count = 0;
	e->in_sim_quote = 0;
	e->in_dob_quote = 0;
}

// Añadir el contenifo de los tokens de dobles comillas
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

// Extraer los tokens
t_token	*extract_dob_quote_token(char *input, int *i)
{
	t_token	*token;
	int		start;

	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (!input[*i])
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_DOB_QUOTE;
	token->value = ft_strndup(&input[start], *i - start);
	(*i)++;
	return (token);
}
