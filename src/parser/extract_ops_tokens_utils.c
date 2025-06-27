/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ops_tokens_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:19:12 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/27 16:02:22 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
