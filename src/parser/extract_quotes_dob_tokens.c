/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_dob_tokens.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:15 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/02 15:32:31 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	**extract_dob_quote_tokens(char *input)
{
	t_token	**tokens;
	t_token	*new_token;
	int		i;
	int		start;
	int		count;
	int		in_double_quote;
	int		in_single_quote;

	count = count_quotes_dob_tokens(input);
	tokens = malloc(sizeof(t_token *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	start = -1;
	count = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
		{
			if (in_double_quote)
			{
				in_double_quote = 0;
				new_token = malloc(sizeof(t_token));
				if (!new_token)
					return (NULL);
				new_token->type = TOKEN_DOB_QUOTE;
				new_token->value = ft_strndup(&input[start], i - start);
				tokens[count++] = new_token;
			}
			else
			{
				in_double_quote = 1;
				start = i + 1;
			}
		}
		i++;
	}
	tokens[count] = NULL;
	return (tokens);
}


