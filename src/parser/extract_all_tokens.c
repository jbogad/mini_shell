/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:47:31 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/28 16:11:59 by clalopez         ###   ########.fr       */
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

t_token	**extract_all_tokens(char *input)
{
	t_token	**tokens;
	t_token	*token;
	int		i;
	int		token_count;
	int		len;

	i = 0;
	token_count = 0;
	len = ft_strlen(input);
	tokens = malloc(sizeof(t_token *) * (len + 1));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		token = get_next_token(input, &i);
		if (token)
			tokens[token_count++] = token;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
