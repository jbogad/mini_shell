/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:15:45 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/18 15:46:56 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc(t_token **tokens)
{
	int		i;
	char	*to_search;
	char	*her_input;

	i = 0;
	while (tokens && tokens[i] != NULL)
	{
		if (tokens[i]->type == TOKEN_HEREDOC && tokens[i + 1] && (tokens[i
				+ 1]->type == TOKEN_WORD || tokens[i
				+ 1]->type == TOKEN_SIM_QUOTE || tokens[i
				+ 1]->type == TOKEN_DOB_QUOTE))
		{
			to_search = ft_strdup(tokens[i + 1]->value);
			her_input = NULL;
			while (1)
			{
				if (her_input)
					free(her_input);
				her_input = readline(">");
				if (!her_input || ft_strcmp(to_search, her_input) == 0)
					break ;
			}
			free(her_input);
			free(to_search);
			i++;
		}
		i++;
	}
}
