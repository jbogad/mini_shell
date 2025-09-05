/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/03 14:51:19 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_commands(t_token **tokens)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
			count++;
		i++;
	}
	return (count);
}

void	setup_child_pipes(int i, int total, int pipes[2][2])
{
	if (i > 0)
	{
		dup2(pipes[(i - 1) % 2][0], STDIN_FILENO);
		close(pipes[(i - 1) % 2][0]);
		close(pipes[(i - 1) % 2][1]);
	}
	if (i < total - 1)
	{
		dup2(pipes[i % 2][1], STDOUT_FILENO);
		close(pipes[i % 2][0]);
		close(pipes[i % 2][1]);
	}
}

void	close_parent_pipes(int i, int pipes[2][2])
{
	if (i > 0)
	{
		close(pipes[(i - 1) % 2][0]);
		close(pipes[(i - 1) % 2][1]);
	}
}

void	wait_for_children(void)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
}
