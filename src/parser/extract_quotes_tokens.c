/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:47:15 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/02 13:16:42 by clalopez         ###   ########.fr       */
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
