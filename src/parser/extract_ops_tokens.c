/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ops_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:51:27 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/09 15:49:27 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Funcion para contar el numero de tokens operadores que hay en el input
int	count_operator_tokens(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			count++;
			i++;
		}
		else if ((input[i] == '<' && input[i + 1] && input[i + 1] == '<') ||
				(input[i] == '>' && input[i + 1] && input[i + 1] == '>'))
		{
			count++;
			i += 2;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}


// Funcion para extrae la barra
t_token	*extract_pipe_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '|')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_PIPE;
		new_token->value = ft_strdup("|");
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
		(*i)++;
		return (new_token);
	}
	return (NULL);
}

// Funcion para extraer << y >>
t_token	*extract_double_redir_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_HEREDOC;
		new_token->value = ft_strdup("<<");
		(*i) += 2;
		return (new_token);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_APPEND;
		new_token->value = ft_strdup(">>");
		(*i) += 2;
		return (new_token);
	}
	return (NULL);
}

// Funcion para extraer < y >
t_token	*extract_single_redir_token(char *input, int *i)
{
	t_token	*new_token;

	if (input[*i] == '<')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_REDIR_IN;
		new_token->value = ft_strdup("<");
		(*i)++;
		return (new_token);
	}
	else if (input[*i] == '>')
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->type = TOKEN_REDIR_OUT;
		new_token->value = ft_strdup(">");
		(*i)++;
		return (new_token);
	}
	return (NULL);
}

// Putisima norminette
t_token	**extract_ops_tokens(char *input)
{
	t_token	**tokens;
	int		token_count;

	token_count = 0;
	tokens = malloc(sizeof(t_token *) * (count_operator_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	fill_operator_tokens(input, tokens, &token_count);
	tokens[token_count] = NULL;
	return (tokens);
}
