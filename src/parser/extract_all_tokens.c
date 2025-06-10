/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:47:31 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/10 11:53:22 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	**extract_all_tokens(char *input)
{
	t_token		**tokens;
	t_token		**tmp;
	t_extract	e;
	int			total;

	total = count_total_tokens(input);
	tokens = malloc(sizeof(t_token *) * (total + 1));
	if (!tokens)
		return (NULL);
	e.index = 0;
	tmp = extract_word_token(input);
	loop_add_tokens(tmp, tokens, &e.index);
	tmp = extract_ops_tokens(input);
	loop_add_tokens(tmp, tokens, &e.index);
	tmp = extract_sim_quote_tokens(input);
	loop_add_tokens(tmp, tokens, &e.index);
	tmp = extract_dob_quote_tokens(input);
	loop_add_tokens(tmp, tokens, &e.index);
	tokens[e.index] = NULL;
	return (tokens);
}
