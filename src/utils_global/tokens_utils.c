/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:12:11 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/17 11:12:58 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_or_free_token(t_token *token, t_token **tokens, int *count)
{
	if (!token)
		return ;
	if (token->value && token->value[0] != '\0')
		tokens[(*count)++] = token;
	else
	{
		free(token->value);
		free(token);
	}
}

/**
 * @brief Añade tokens de un array temporal a otro array principal.
 * @param tmp Array temporal de tokens para agregar.
 * @param tokens Array principal donde se añaden los tokens.
 * @param index Puntero al índice actual en `tokens`; se incrementa c
 * on cada token añadido.
 */
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
