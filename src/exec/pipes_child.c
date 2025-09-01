/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/31 12:37:37 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	**get_cmd_tokens(t_token **tokens, int cmd_idx)
{
	t_token	**cmd_tokens;
	int		i;
	int		j;
	int		pipes_passed;
	int		cmd_length;

	i = 0;
	pipes_passed = 0;
	while (tokens[i] && pipes_passed < cmd_idx)
	{
		if (tokens[i]->type == TOKEN_PIPE)
			pipes_passed++;
		i++;
	}
	j = i;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
		j++;
	cmd_length = j - i;
	if (cmd_length == 0)
		return (NULL);
	cmd_tokens = malloc(sizeof(t_token *) * (cmd_length + 1));
	if (!cmd_tokens)
		return (NULL);
	j = 0;
	while (j < cmd_length)
	{
		cmd_tokens[j] = tokens[i + j];
		j++;
	}
	cmd_tokens[j] = NULL;
	return (cmd_tokens);
}

static void	free_cmd_tokens(t_token **tokens)
{
	if (tokens)
		free(tokens);
}

void	process_pipe_child(t_token **tokens, int i, int total,
			int pipes[2][2], t_shell *msh)
{
	char	**argv;
	t_token	**cmd_tokens;

	cmd_tokens = get_cmd_tokens(tokens, i);
	setup_child_pipes(i, total, pipes);
	if (cmd_tokens && msh)
		set_redirections(cmd_tokens, msh, -1);
	argv = build_cmd(tokens, i);
	if (argv && argv[0] && execvp(argv[0], argv) == -1)
	{
		free_cmd_tokens(cmd_tokens);
		exit(1);
	}
	free_cmd_tokens(cmd_tokens);
	exit(1);
}
