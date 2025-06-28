/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_sim_tokens.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:21:51 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/28 11:58:12 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Contar cuantos tokens de comillas simples hay
int	count_quotes_sim_tokens(char *input)
{
	int	i;
	int	count;
	int	in_sim_quote;
	int	in_dob_quote;

	i = 0;
	count = 0;
	in_sim_quote = 0;
	in_dob_quote = 0;
	while (input[i++])
	{
		if (input[i - 1] == '"' && !in_sim_quote)
			in_dob_quote = !in_dob_quote;
		else if (input[i - 1] == '\'' && !in_dob_quote)
		{
			if (in_sim_quote)
			{
				in_sim_quote = 0;
				count++;
			}
			else
				in_sim_quote = 1;
		}
	}
	return (count);
}

// Inicializar las variables para extraer los tokens
void	init_extract(t_extract *e)
{
	e->i = 0;
	e->start = -1;
	e->count = 0;
	e->in_sim_quote = 0;
	e->in_dob_quote = 0;
}

// Añadir el contenifo de los tokens de comillas simples
void	fill_sim_quote_tokens(char *input, t_token **tokens, t_extract *e)
{
	t_token	*new_tkn;

	init_extract(e);
	while (input[e->i])
	{
		if (input[e->i] == '"' && !e->in_sim_quote)
			e->in_dob_quote = !e->in_dob_quote;
		else if (input[e->i] == '\'' && !e->in_dob_quote)
		{
			if (e->in_sim_quote)
			{
				e->in_sim_quote = 0;
				new_tkn = malloc(sizeof(t_token));
				new_tkn->type = TOKEN_SIM_QUOTE;
				new_tkn->value = ft_strndup(&input[e->start], e->i - e->start);
				tokens[e->count++] = new_tkn;
			}
			else
			{
				e->start = e->i + 1;
				e->in_sim_quote = 1;
			}
		}
		e->i++;
	}
}

// Extraer los tokens
t_token	*extract_sim_quote_token(char *input, int *i)
{
	t_token	*token;
	int		start;

	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_SIM_QUOTE;
	token->value = ft_strndup(&input[start], *i - start);
	(*i)++;
	return (token);
}
