/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_sim_tokens.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:21:51 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/02 15:35:18 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	**extract_sim_quote_tokens(char *input)
{
	t_token	**tokens;
	t_token	*new_token;
	int		i;
	int		start;
	int		count;
	int		in_sim_quote;
	int		in_dob_quote;

	count = count_quotes_sim_tokens(input);
	tokens = malloc(sizeof(t_token *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	start = -1;
	count = 0;
	in_sim_quote = 0;
	in_dob_quote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !in_sim_quote)
			in_dob_quote = !in_dob_quote;
		else if (input[i] == '\'' && !in_dob_quote)
		{
			if (in_sim_quote)
			{
				in_sim_quote = 0;
				new_token = malloc(sizeof(t_token));
				if (!new_token)
					return (NULL);
				new_token->type = TOKEN_SIM_QUOTE;
				new_token->value = ft_strndup(&input[start], i - start);
				tokens[count++] = new_token;
			}
			else
			{
				in_sim_quote = 1;
				start = i + 1;
			}
		}
		i++;
	}
	tokens[count] = NULL;
	return (tokens);
}
