/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/17 15:31:36 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_cmd_tokens(t_pipe_data *data)
{
	int	i;
	int	j;
	int	pipes_passed;

	i = 0;
	pipes_passed = 0;
	while (data->tokens[i] && pipes_passed < data->cmd_idx)
	{
		if (data->tokens[i]->type == TOKEN_PIPE)
		{
			pipes_passed++;
			while (data->tokens[i] && data->tokens[i]->type == TOKEN_PIPE)
				i++;
			i--;
		}
		i++;
	}
	j = i;
	while (data->tokens[j] && data->tokens[j]->type != TOKEN_PIPE)
		j++;
	return (j - i);
}

static void	fill_cmd_tokens(t_pipe_data *data, t_token **cmd_tokens, int start)
{
	int	i;
	int	count;

	count = count_cmd_tokens(data);
	i = 0;
	while (i < count)
	{
		cmd_tokens[i] = data->tokens[start + i];
		i++;
	}
	cmd_tokens[i] = NULL;
}

static int	skip_pipes(t_token **tokens, int i)
{
	while (tokens[i] && tokens[i]->type == TOKEN_PIPE)
		i++;
	return (i - 1);
}

t_token	**get_cmd_tokens(t_pipe_data *data)
{
	t_token	**cmd_tokens;
	int		i;
	int		pipes_passed;
	int		count;

	i = 0;
	pipes_passed = 0;
	while (data->tokens[i] && pipes_passed < data->cmd_idx)
	{
		if (data->tokens[i]->type == TOKEN_PIPE)
		{
			pipes_passed++;
			i = skip_pipes(data->tokens, i);
		}
		i++;
	}
	count = count_cmd_tokens(data);
	if (count == 0)
		return (NULL);
	cmd_tokens = malloc(sizeof(t_token *) * (count + 1));
	if (!cmd_tokens)
		return (NULL);
	fill_cmd_tokens(data, cmd_tokens, i);
	return (cmd_tokens);
}
